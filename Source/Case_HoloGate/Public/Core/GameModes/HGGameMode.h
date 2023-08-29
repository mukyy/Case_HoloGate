// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "HGGameMode.generated.h"

/**
 * AHGGameMode
 *
 *  Base game mode that is used in this project by default.
 */
UCLASS(Blueprintable, Meta = (ShortTooltip = "The base game mode class used by this project."))
class CASE_HOLOGATE_API AHGGameMode : public AGameMode
{
	GENERATED_BODY()
	
};
