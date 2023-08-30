// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "HGCharacter.generated.h"

class UHGCharacterMovementComponent;
class UHGWeaponComponent;
class UHGAttributesComponent;
class UHGPawnExtensionComponent;
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
	AHGCharacter(const FObjectInitializer& ObjectInitializer);

private:
	UPROPERTY(EditDefaultsOnly)
	UHGPawnExtensionComponent* PawnExtensionComponent;
	UPROPERTY(EditDefaultsOnly)
	UHGCharacterMovementComponent* MovementComponent;
	UPROPERTY(EditDefaultsOnly)
	UHGAttributesComponent* AttributesComponent;
	UPROPERTY(EditDefaultsOnly)
	UHGWeaponComponent* WeaponComponent;

public:
	// Gets the controller of this pawn.
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	AHGPlayerController* GetHGPlayerController() const;

	// Gets the player state of this pawn.
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	AHGPlayerState* GetHGPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	UHGPawnExtensionComponent* GetPawnExtensionComponent() const;
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	UHGCharacterMovementComponent* GetCharacterMovementComponent() const;
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	UHGAttributesComponent* GetAttributesComponent() const;
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	UHGWeaponComponent* GetWeaponComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
