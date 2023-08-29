// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HGPlayerController.generated.h"

/**
 * AHGPlayerController
 *
 *	The base player controller class used by this project.
 */
UCLASS(Blueprintable, Config = Game, Meta = (ShortTooltip = "The base player controller class used by this project."))
class CASE_HOLOGATE_API AHGPlayerController : public APlayerController
{
	GENERATED_BODY()
};
