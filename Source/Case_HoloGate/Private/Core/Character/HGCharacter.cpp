// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/HGCharacter.h"

#include "HGLogChannels.h"
#include "Camera/CameraComponent.h"
#include "Core/Player/HGPlayerController.h"
#include "Core/Player/HGPlayerState.h"
#include "Core/Components/HGPawnExtensionComponent.h"
#include "Core/Components/HGAttributesComponent.h"
#include "Core/Components/HGMovementComponent.h"
#include "Core/Components/HGWeaponComponent.h"
#include "GameFramework/SpringArmComponent.h"


AHGCharacter::AHGCharacter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);

	WeaponSocketComponent = CreateDefaultSubobject<USceneComponent>(FName("Weapon Socket"));
	WeaponSocketComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName("Spring Arm"));
	SpringArmComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	SpringArmComponent->TargetArmLength = 800.0f;
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	
	PawnExtensionComponent = CreateDefaultSubobject<UHGPawnExtensionComponent>(FName("Pawn Extension Component"));
	AttributesComponent = CreateDefaultSubobject<UHGAttributesComponent>(FName("Attributes Component"));
	WeaponComponent = CreateDefaultSubobject<UHGWeaponComponent>(FName("Weapon Component"));
}

UHGPawnExtensionComponent* AHGCharacter::GetPawnExtensionComponent() const
{
	if (PawnExtensionComponent == nullptr)
	{
		Error_MissingComponent(UHGPawnExtensionComponent::StaticClass());
		return nullptr;
	}
	return PawnExtensionComponent;
}

UHGAttributesComponent* AHGCharacter::GetAttributesComponent() const
{
	if (AttributesComponent == nullptr)
	{
		Error_MissingComponent(UHGAttributesComponent::StaticClass());
		return nullptr;
	}
	return AttributesComponent;
}

UHGWeaponComponent* AHGCharacter::GetWeaponComponent() const
{
	if (WeaponComponent == nullptr)
	{
		Error_MissingComponent(UHGWeaponComponent::StaticClass());
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

USpringArmComponent* AHGCharacter::GetSpringArmComponent() const
{
	if (SpringArmComponent == nullptr)
	{
		Error_MissingComponent(USpringArmComponent::StaticClass());
		return nullptr;
	}
	return SpringArmComponent;
}

UCameraComponent* AHGCharacter::GetCameraComponent() const
{
	if (CameraComponent == nullptr)
	{
		Error_MissingComponent(UCameraComponent::StaticClass());
		return nullptr;
	}
	return CameraComponent;
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

