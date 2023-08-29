// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "HGPlayerState.generated.h"

/**
 * AHGPlayerState
 *
 *	Base player state class used by this project.
 */
UCLASS(Blueprintable, Meta = (ShortTooltip = "The base player state class used by this project."))
class CASE_HOLOGATE_API AHGPlayerState : public APlayerState
{
	GENERATED_BODY()
};
