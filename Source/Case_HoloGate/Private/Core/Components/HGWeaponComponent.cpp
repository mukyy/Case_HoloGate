// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/HGWeaponComponent.h"

#include "HGLogChannels.h"
#include "Core/Weapons/HGWeapon.h"
#include "Core/Weapons/HGWeaponData.h"
#include "Net/UnrealNetwork.h"

UHGWeaponComponent::UHGWeaponComponent()
{
	SetIsReplicatedByDefault(true);
}

void UHGWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHGWeaponComponent, WeaponInstance);
	DOREPLIFETIME(UHGWeaponComponent, CurrentWeaponData);
}

void UHGWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_Authority)
	{
		EquipNewWeapon(DefaultWeaponData);
	}
}

void UHGWeaponComponent::Server_EquipNewWeapon_Implementation(UHGWeaponData* newWeaponData)
{
	EquipNewWeapon(newWeaponData);
}

void UHGWeaponComponent::Server_UnequipCurrentWeapon_Implementation()
{
	UnequipCurrentWeapon();
}

void UHGWeaponComponent::OnRep_WeaponInstance()
{
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

void UHGWeaponComponent::SetWeaponSocketComponent(USceneComponent* WeaponSocket)
{
	if (WeaponSocket == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Weapon Socket component was null when trying to set it."))
		return;
	}
	WeaponSocketComponent = WeaponSocket;
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
