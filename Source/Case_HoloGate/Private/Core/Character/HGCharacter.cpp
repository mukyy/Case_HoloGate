// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Character/HGCharacter.h"

#include "Core/Player/HGPlayerController.h"
#include "Core/Player/HGPlayerState.h"


// Sets default values
AHGCharacter::AHGCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

