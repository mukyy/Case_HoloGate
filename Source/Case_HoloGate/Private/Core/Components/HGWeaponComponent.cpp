// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/HGWeaponComponent.h"

#include "HGLogChannels.h"
#include "Core/Character/HGCharacter.h"
#include "Core/Player/HGPlayerController.h"
#include "Core/Weapons/HGWeapon.h"
#include "Core/Weapons/HGWeaponData.h"
#include "Core/Weapons/HGWeaponProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Net/UnrealNetwork.h"

UHGWeaponComponent::UHGWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UHGWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHGWeaponComponent, WeaponInstance);
	DOREPLIFETIME(UHGWeaponComponent, CurrentWeaponData);
	DOREPLIFETIME(UHGWeaponComponent, bIsFiringInputHeld);
	
	// We dont need to know this since we are setting these directly with inputs.
	DOREPLIFETIME_CONDITION(UHGWeaponComponent, DesiredAimRotation, COND_SkipOwner);

}

void UHGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	EquipNewWeapon(DefaultWeaponData);
}

void UHGWeaponComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	
	if (HasEquippedWeapon())
	{
		// Destroy our spawned weapon instance when being destroyed.
		GetWeaponInstance()->Destroy();
	}
}

void UHGWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwnerCharacter() == nullptr)
	{
		return;
	}

	if (GetWeaponSocketComponent() == nullptr)
	{
		return;
	}
	
	if (GetOwnerCharacter()->IsLocallyControlled())
	{
		AHGPlayerController* pc = GetOwnerCharacter()->GetHGPlayerController();
		FRotator currentRotation = pc->GetControlRotation();
		FHitResult cursorHitResult;
		pc->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, cursorHitResult);

	
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetWeaponSocketComponent()->GetComponentLocation(), cursorHitResult.Location);

		// So we only use yaw values since we have top down tanks.
		targetRotation.Pitch = 0.0f;
		targetRotation.Roll = 0.0f;
		
		FRotator interpolatedRotation = UKismetMathLibrary::RInterpTo_Constant(currentRotation, targetRotation, DeltaTime, CalculateRotationInterpSpeed());

		// Unreal sends this value to serverside internally.
		pc->SetControlRotation(interpolatedRotation);
		// However set the rotation of the weapon instantly if we are the local player for responsiveness.
		GetWeaponSocketComponent()->SetWorldRotation(interpolatedRotation);
		if (GetOwner()->HasAuthority())
		{
			SetDesiredAimRotation(GetOwnerCharacter()->GetHGPlayerController()->GetControlRotation());
		}
	}
	// Other players
	else
	{
		if (GetOwner()->HasAuthority())
		{
			SetDesiredAimRotation(GetOwnerCharacter()->GetHGPlayerController()->GetControlRotation());
		}
		
		// Smoothen the rotation on clients.
		FRotator interpolatedRotation = UKismetMathLibrary::RInterpTo_Constant(GetWeaponSocketComponent()->GetComponentRotation(), GetDesiredAimRotation(), DeltaTime, CalculateRotationInterpSpeed());
		GetWeaponSocketComponent()->SetWorldRotation(interpolatedRotation);
	}
}

bool UHGWeaponComponent::IsFiringInputHeld() const
{
	return bIsFiringInputHeld;
}

UHGWeaponData* UHGWeaponComponent::GetCurrentWeaponData() const
{
	if (CurrentWeaponData == nullptr)
	{
		UE_LOG(LogHGDebug, Warning, TEXT("Tried accessing weapon data when no weapon data was present."));
		return nullptr;
	}
	return CurrentWeaponData;
}

void UHGWeaponComponent::Server_EquipNewWeapon_Implementation(UHGWeaponData* newWeaponData)
{
	EquipNewWeapon(newWeaponData);
}

void UHGWeaponComponent::Server_UnequipCurrentWeapon_Implementation()
{
	UnequipCurrentWeapon();
}

void UHGWeaponComponent::OnRep_IsFiringInputHeld()
{
	if (!GetOwnerCharacter()->IsLocallyControlled())
	{
		if (!IsFiringInputHeld())
		{
			StopFiring();
			return;
		}
		Fire();
	}
}

float UHGWeaponComponent::CalculateRotationInterpSpeed() const
{
	UHGWeaponData* weaponData = GetCurrentWeaponData();

	if (weaponData == nullptr)
	{
		return RotationInterpSpeed;
	}
	
	return RotationInterpSpeed * weaponData->WeaponData.HandleData.RotationSpeedModifier; 
}



USceneComponent* UHGWeaponComponent::GetWeaponSocketComponent() const
{
	if (WeaponSocketComponent == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Weapon Socket component is null!"))
		return nullptr;
	}

	return WeaponSocketComponent;
}

void UHGWeaponComponent::SetWeaponSocketComponent(USceneComponent* weaponSocket)
{
	if (weaponSocket == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Weapon Socket component was null when trying to set it."))
		return;
	}
	WeaponSocketComponent = weaponSocket;
}

FRotator UHGWeaponComponent::GetDesiredAimRotation() const
{
	return DesiredAimRotation;
}

void UHGWeaponComponent::SetDesiredAimRotation(const FRotator newAimRotation)
{
	DesiredAimRotation = newAimRotation;
}

bool UHGWeaponComponent::HasEquippedWeapon() const
{
	return WeaponInstance != nullptr;
}

bool UHGWeaponComponent::CanEquipNewWeapon() const
{
	//TODO: 
	return true;
}

void UHGWeaponComponent::EquipNewWeapon(UHGWeaponData* newWeaponData)
{
	if (newWeaponData == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Equip Weapon is called with null weapon data parameter!"));
		return;
	}
	if (GetOwnerRole() != ROLE_Authority)
	{
		Server_EquipNewWeapon(newWeaponData);
		return;
	}
	
	if (!CanEquipNewWeapon())
	{
		UE_LOG(LogHGDebug, Display, TEXT("Cannot equip a new weapon"));
		return;
	}
	
	if (HasEquippedWeapon())
	{
		UnequipCurrentWeapon();
	}

	if (newWeaponData->WeaponVisualClass == nullptr)
	{
		UE_LOG(LogHG, Warning, TEXT("Weapon Data is missing visual weapon blueprint!"));
		return;
	}
	
	WeaponInstance = GetWorld()->SpawnActor<AHGWeapon>(newWeaponData->WeaponVisualClass, FTransform());
	WeaponInstance->AttachToComponent(GetWeaponSocketComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CurrentWeaponData = newWeaponData;
}

void UHGWeaponComponent::UnequipCurrentWeapon()
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		Server_UnequipCurrentWeapon();
		return;
	}

	if (WeaponInstance == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Attempted to unequip weapon when weapon instance was already null!"));
		return;
	}
	
	WeaponInstance->Destroy();
	WeaponInstance = nullptr;
}

AHGWeapon* UHGWeaponComponent::GetWeaponInstance() const
{
	if (WeaponInstance == nullptr)
	{
		UE_LOG(LogHG, Warning, TEXT("Attempted to access weapon instance when there is no weapon equipped from: %s actor!"), *GetOwner()->GetName());
		return nullptr;
	}
	return WeaponInstance;
}

void UHGWeaponComponent::Fire_Implementation()
{
	if (!CanKeepFiring() ||
		GetCurrentWeaponData() == nullptr ||
		GetCurrentWeaponData()->WeaponData.FiringData.ProjectileClass == nullptr ||
		WeaponInstance == nullptr)
	{
		StopFiring();
		return;
	}

	AHGWeaponProjectile* spawnedProjectile = GetWorld()->SpawnActor<AHGWeaponProjectile>(GetCurrentWeaponData()->WeaponData.FiringData.ProjectileClass, WeaponInstance->GetMuzzleLocation(), FRotator::ZeroRotator);
	FVector velocity = GetWeaponSocketComponent()->GetForwardVector() * GetCurrentWeaponData()->WeaponData.FiringData.ProjectileSpeed;
	velocity.Z = 0.0f;

	spawnedProjectile->ProjectileSpawned(velocity);
	spawnedProjectile->SetDamage(GetCurrentWeaponData()->WeaponData.FiringData.Damage);
	spawnedProjectile->SetInstigator(GetOwnerCharacter());

	// Calls itself recursively
	GetWorld()->GetTimerManager().SetTimer(FiringHandle, this, &UHGWeaponComponent::Fire, GetCurrentWeaponData()->WeaponData.FiringData.FireRate, false);
}

void UHGWeaponComponent::Server_StartFiring_Implementation()
{
	StartFiring();
}

void UHGWeaponComponent::StartFiring()
{
	if (!HasEquippedWeapon() ||
		!CanStartFiring())
	{
		return;
	}
	
	if (GetOwnerRole() != ROLE_Authority)
	{
		Server_StartFiring();
	}

	bIsFiringInputHeld = true;
	Fire();
}

void UHGWeaponComponent::Server_StopFiring_Implementation()
{
	StopFiring();
}

void UHGWeaponComponent::StopFiring()
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		Server_StopFiring();
	}
	bIsFiringInputHeld = false;
}

bool UHGWeaponComponent::CanStartFiring()
{
	bool canStartFire = true;
	canStartFire = !GetWorld()->GetTimerManager().IsTimerActive(FiringHandle);
	return canStartFire;
}

bool UHGWeaponComponent::CanKeepFiring()
{
	bool canFire = true;
	canFire = bIsFiringInputHeld;
	return canFire;
}

bool UHGWeaponComponent::IsFiring() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(FiringHandle);
}
