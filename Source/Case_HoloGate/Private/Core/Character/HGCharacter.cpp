// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/HGCharacter.h"

#include "HGLogChannels.h"
#include "Core/Player/HGPlayerController.h"
#include "Core/Player/HGPlayerState.h"
#include "Core/Components/HGPawnExtensionComponent.h"
#include "Core/Components/HGAttributesComponent.h"
#include "Core/Components/HGMovementComponent.h"
#include "Core/Components/HGWeaponComponent.h"


AHGCharacter::AHGCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
	
	PawnExtensionComponent = CreateDefaultSubobject<UHGPawnExtensionComponent>(FName("Pawn Extension Component"));
	MovementComponent = CreateDefaultSubobject<UHGCharacterMovementComponent>(FName("Character Movement"));
	AttributesComponent = CreateDefaultSubobject<UHGAttributesComponent>(FName("Attributes Component"));
	WeaponComponent = CreateDefaultSubobject<UHGWeaponComponent>(FName("Weapon Component"));
}

UHGPawnExtensionComponent* AHGCharacter::GetPawnExtensionComponent() const
{
	if (PawnExtensionComponent == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Pawn Extension Component is missing!"));
		return nullptr;
	}
	return PawnExtensionComponent;
}

UHGCharacterMovementComponent* AHGCharacter::GetCharacterMovementComponent() const
{
	if (MovementComponent == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Character Movement Component is missing!"));
		return nullptr;
	}
	return MovementComponent;
}

UHGAttributesComponent* AHGCharacter::GetAttributesComponent() const
{
	if (AttributesComponent == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Attributes Component is missing!"));
		return nullptr;
	}
	return AttributesComponent;
}

UHGWeaponComponent* AHGCharacter::GetWeaponComponent() const
{
	if (WeaponComponent == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Weapon Component is missing!"));
		return nullptr;
	}
	return WeaponComponent;
}

AHGPlayerController* AHGCharacter::GetHGPlayerController() const
{
	return CastChecked<AHGPlayerController>(Controller, ECastCheckedType::NullAllowed);
}

AHGPlayerState* AHGCharacter::GetHGPlayerState() const
{
	return CastChecked<AHGPlayerState>(GetPlayerState(), ECastCheckedType::NullAllowed);
}

// Called when the game starts or when spawned
void AHGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

