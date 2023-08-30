// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/HGComponent.h"
#include "HGPawnComponent.generated.h"

CASE_HOLOGATE_API DECLARE_LOG_CATEGORY_EXTERN(LogLyraTeams, Log, All);


/**
 * UHGPawnComponent
 *
 *  Base component that all components that can be attached to pawn should be deriving from.
 *  Prevents adding this component to any class that is not a Pawn.
 *  Purpose of this component is to have common ground for all pawn components.
 */
UCLASS(Meta = (ShortTooltip = "Base actor component used for Pawns exclusively."))
class CASE_HOLOGATE_API UHGPawnComponent : public UHGComponent
{
	GENERATED_BODY()
	
};
