// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HGCharacter.generated.h"

class AHGPlayerController;
class AHGPlayerState;

/**
 * AHGCharacter
 *
 *	The base character pawn class used by this project.
 *	Responsible for sending events to pawn components.
 *	New behavior should be added via pawn components when possible.
 */
UCLASS(Blueprintable, Config = Game, Meta = (ShortTooltip = "The base character pawn class used by this project."))
class CASE_HOLOGATE_API AHGCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHGCharacter();

	// Gets the controller of this pawn.
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	AHGPlayerController* GetHGPlayerController() const;

	// Gets the player state of this pawn.
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	AHGPlayerState* GetHGPlayerState() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
