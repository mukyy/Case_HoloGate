// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGWeaponProjectile.generated.h"

USTRUCT(BlueprintType)
struct FProjectileData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float HitRadius;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProjectileExploded, TArray<AActor*>, HitActors);

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
	// Value must be coming from the weapon this projectile is fired from.
	float Damage;
	
	// Trace channel used to find hit actors.
	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> TraceChannel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	float GetDamage() const;

	UFUNCTION(BlueprintCallable)
	void SetDamage(float NewValue);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintAssignable)
	FOnProjectileExploded OnProjectileExploded;
};
