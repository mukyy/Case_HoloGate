// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HGWeaponData.generated.h"

class AHGWeapon;
class AHGWeaponProjectile;

USTRUCT(BlueprintType)
struct FWeaponEquipData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FTransform EquipOffset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EquipSpeed = 0.25f;	
};

USTRUCT(BlueprintType)
struct FWeaponClipData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxSize = 30.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ReloadDuration = 0.5f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ReloadConsumeRate = 1.0f;
};

USTRUCT(BlueprintType)
struct FWeaponFiringData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage = 10.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FireRate = 0.25f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHGWeaponProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ProjectileSpeed = 1000.0f;
};

USTRUCT(BlueprintType)
struct FWeaponHandleData
{
	GENERATED_BODY()

	// Coefficient for how fast our weapon rotation reaches the direction to the mouse.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RotationSpeedModifier = 1.0f;

	// Coefficient for character's movement speed, allows "Heavy" weapons to apply penalty.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MovementSpeedModifier = 1.0f;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWeaponFiringData FiringData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWeaponHandleData HandleData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWeaponEquipData EquipData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWeaponClipData ClipData;
};

/**
 * UHGWeaponData
 *
 *  Contains every data type related to weapon systems.
 *  Has both visual and gameplay logic data.
 */
UCLASS(Meta = (ShortTooltip = "Contains necessary data for weapons to drive the weapon systems."))
class CASE_HOLOGATE_API UHGWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AHGWeapon> WeaponVisualClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FWeaponData WeaponData;
};
