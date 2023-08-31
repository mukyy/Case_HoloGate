// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGWeapon.generated.h"

/**
 * AHGWeapon
 *
 *  Base abstract weapon actor to represent visuals for the weapons.
 *  Contains cosmetic logic to drive visuals for the weapons e.g: Sounds, Traces, Decals, etc.
 */
UCLASS(Abstract, Blueprintable, Meta = (ShortTooltip = "The base abstract weapon actor."))
class CASE_HOLOGATE_API AHGWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHGWeapon();

public:
	// Spawn location for the bullets.
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	FVector GetMuzzleLocation() const;
};
