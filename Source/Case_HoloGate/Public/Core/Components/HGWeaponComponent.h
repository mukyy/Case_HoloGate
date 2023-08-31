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
	
	UFUNCTION(Server, Reliable)
	void Server_StartFiring();
	
	UFUNCTION(Server, Reliable)
	void Server_StopFiring();
	
	UPROPERTY()
	USceneComponent* WeaponSocketComponent;
	
	UPROPERTY(ReplicatedUsing=OnRep_WeaponInstance)
	AHGWeapon* WeaponInstance;


	// Controls base interp speed for weapon rotation.
	UPROPERTY(EditDefaultsOnly)
	float RotationInterpSpeed = 700.0f;
	
	UPROPERTY(EditDefaultsOnly)
	UHGWeaponData* DefaultWeaponData;

	UPROPERTY(Replicated, VisibleInstanceOnly)
	UHGWeaponData* CurrentWeaponData;

	// Player controllers are not shared to other clients, DesiredAimRotation helps us replicate this value to other clients too.
	UPROPERTY(Replicated, VisibleInstanceOnly)
	FRotator DesiredAimRotation;

	FTimerHandle FiringHandle;

	UPROPERTY(Replicated)
	bool bIsFiringInputHeld;
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	AHGWeapon* GetWeaponInstance() const;

	UFUNCTION()
	void OnRep_WeaponInstance();

	// Calculates interp speed based on BaseRotationSpeed & Weapon rotation penalty.
	float CalculateRotationInterpSpeed() const;

	// Cosmetic events can be set up in blueprint side. Gets called every time weapon is fired.
	UFUNCTION(BlueprintNativeEvent)
	void Fire();
	
public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool IsFiringInputHeld() const;
	
	UFUNCTION(BlueprintCallable)
	UHGWeaponData* GetCurrentWeaponData() const;

	UFUNCTION(BlueprintCallable)
	USceneComponent* GetWeaponSocketComponent() const;
	
	void SetWeaponSocketComponent(USceneComponent* WeaponSocket);

	UFUNCTION(BlueprintCallable)
	FRotator GetDesiredAimRotation() const;

	UFUNCTION(BlueprintCallable)
	void SetDesiredAimRotation(const FRotator newAimRotation);
	
	UFUNCTION(BlueprintCallable)
	bool HasEquippedWeapon() const;

	UFUNCTION(BlueprintCallable)
	bool CanEquipNewWeapon() const;

	UFUNCTION(BlueprintCallable)
	void EquipNewWeapon(UHGWeaponData* newWeaponData);

	UFUNCTION(BlueprintCallable)
	void UnequipCurrentWeapon();

	UFUNCTION(BlueprintCallable)
	void StartFiring();

	UFUNCTION(BlueprintCallable)
	void StopFiring();

	UFUNCTION(BlueprintCallable)
	bool CanStartFiring();

	// Controls how Fire function is called recursively. Beware!
	UFUNCTION(BlueprintCallable)
	bool CanKeepFiring();

	UFUNCTION(BlueprintCallable)
	bool IsFiring() const;

};
