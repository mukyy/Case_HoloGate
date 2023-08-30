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
	UFUNCTION(Server, Reliable)
	void Server_EquipNewWeapon(UHGWeaponData* newWeaponData);

	UFUNCTION(Server, Reliable)
	void Server_UnequipCurrentWeapon();

	UPROPERTY()
	USceneComponent* WeaponSocketComponent;
	
	UPROPERTY(ReplicatedUsing=OnRep_WeaponInstance)
	AHGWeapon* WeaponInstance;

	UPROPERTY(EditDefaultsOnly)
	UHGWeaponData* DefaultWeaponData;

	UPROPERTY(Replicated, VisibleInstanceOnly)
	UHGWeaponData* CurrentWeaponData;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	AHGWeapon* GetWeaponInstance() const;

	UFUNCTION()
	void OnRep_WeaponInstance();

public:
	UFUNCTION(BlueprintCallable)
	USceneComponent* GetWeaponSocketComponent() const;
	
	void SetWeaponSocketComponent(USceneComponent* WeaponSocket);

	UFUNCTION(BlueprintCallable)
	bool HasEquippedWeapon() const;

	UFUNCTION(BlueprintCallable)
	bool CanEquipNewWeapon() const;

	UFUNCTION(BlueprintCallable)
	void EquipNewWeapon(UHGWeaponData* newWeaponData);

	UFUNCTION(BlueprintCallable)
	void UnequipCurrentWeapon();
};
