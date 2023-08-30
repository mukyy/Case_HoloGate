// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HGCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AHGPlayerController;
class AHGPlayerState;
class UHGWeaponComponent;
class UHGAttributesComponent;


/**
 * AHGCharacter
 *
 *	The base character pawn class used by this project.
 *	Responsible for sending events to pawn components.
 *	New behavior should be added via pawn components when possible.
 */
UCLASS(Blueprintable, Config = Game, Meta = (ShortTooltip = "The base character pawn class used by this project."))
class CASE_HOLOGATE_API AHGCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	AHGCharacter(const FObjectInitializer& ObjectInitializer);

private:
	// Spawned weapon visuals gets attached to it, acts as a socket.
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* WeaponSocketComponent;
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraComponent;
	UPROPERTY(EditDefaultsOnly)
	UHGAttributesComponent* AttributesComponent;
	UPROPERTY(EditDefaultsOnly)
	UHGWeaponComponent* WeaponComponent;
	
public:
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	AHGPlayerController* GetHGPlayerController() const;

	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	AHGPlayerState* GetHGPlayerState() const;

	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	USceneComponent* GetWeaponSocketComponent() const;
	
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	USpringArmComponent* GetSpringArmComponent() const;
	
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	UCameraComponent* GetCameraComponent() const;
	
	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	UHGAttributesComponent* GetAttributesComponent() const;

	UFUNCTION(BlueprintCallable, Category = "HoloGate|Character")
	UHGWeaponComponent* GetWeaponComponent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
