﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGWeaponProjectile.generated.h"

class UProjectileMovementComponent;

USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HitRadius;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileExploded, TArray<FOverlapResult>, HitResults);

/**
 * AHGWeaponProjectile
 *
 *  Base abstract projectile class for projectiles.
 *  Get spawned everytime weapon is fired.
 *  Contains both visual and gameplay logic.
 */
UCLASS(Abstract, Blueprintable, Meta = (ShortTooltip = "The base abstract projectile class."))
class CASE_HOLOGATE_API AHGWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHGWeaponProjectile();

private:
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovement;

	// Value must be coming from the weapon this projectile is fired from.
	float Damage;
	
public:
	
	UFUNCTION(BlueprintCallable)
	UProjectileMovementComponent* GetProjectileMovement() const;

	UFUNCTION(BlueprintCallable)
	float GetDamage() const;

	UFUNCTION(BlueprintCallable)
	void SetDamage(float newValue);

	UFUNCTION(BlueprintCallable)
	void ProjectileSpawned(FVector projectileVelocity);

	UFUNCTION(BlueprintCallable)
	void Explode();

	UPROPERTY(BlueprintAssignable)
	FOnProjectileExploded OnProjectileExploded;
};
