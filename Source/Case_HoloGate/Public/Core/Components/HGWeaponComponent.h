// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/HGPawnComponent.h"
#include "HGWeaponComponent.generated.h"

class UHGWeaponData;
class AHGWeapon;

/**
 * UHGWeaponComponent
 *
 *  Handles gameplay functionality of the weapons such as firing, reloading etc.
 */
UCLASS(Blueprintable)
class CASE_HOLOGATE_API UHGWeaponComponent : public UHGPawnComponent
{
	GENERATED_BODY()
	
public:
	UHGWeaponComponent();
	
private:
	UPROPERTY(ReplicatedUsing=OnRep_WeaponInstance)
	AHGWeapon* WeaponInstance;

	UPROPERTY(EditDefaultsOnly)
	UHGWeaponData* DefaultWeaponData;

	UPROPERTY(Replicated)
	UHGWeaponData* CurrentWeaponData;
	
protected:
	UFUNCTION(BlueprintCallable)
	AHGWeapon* GetWeaponInstance() const;

	UFUNCTION()
	void OnRep_WeaponInstance();

public:
	bool HasEquippedWeapon() const;
	bool CanEquipNewWeapon() const;
	void EquipNewWeapon(OUT bool& bIsSuccess);
};
