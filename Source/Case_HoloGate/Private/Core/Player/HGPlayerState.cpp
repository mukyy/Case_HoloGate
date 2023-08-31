// Fill out your copyright notice in the Description page of Project Settings.


#include "Case_HoloGate/Public/Core/Player/HGPlayerState.h"

#include "Core/Character/HGCharacter.h"
#include "GameFramework/GameModeBase.h"

void AHGPlayerState::Killed()
{
	GetPawn()->Destroy();
	StartRespawnTimer();
}

void AHGPlayerState::StartRespawnTimer()
{
	GetWorld()->GetTimerManager().SetTimer(RespawnHandle, this, &AHGPlayerState::Respawn, 5.0f, false);
}

void AHGPlayerState::Respawn()
{
	//TODO: Carry over to gamestate or gamemode preferably.
	if (!HasAuthority())
	{
		return;	
	}
	GetWorld()->GetAuthGameMode()->RestartPlayer(GetOwningController());	
}
