// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/HGWeaponComponent.h"

#include "HGLogChannels.h"
#include "Core/Weapons/HGWeapon.h"
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

void UHGWeaponComponent::OnRep_WeaponInstance()
{
}

bool UHGWeaponComponent::HasEquippedWeapon() const
{
	return WeaponInstance != nullptr;
}

bool UHGWeaponComponent::CanEquipNewWeapon() const
{
	return true;
}

void UHGWeaponComponent::EquipNewWeapon(bool& bIsSuccess)
{
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
