// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/HGComponent.h"
#include "HGPawnComponent.generated.h"


class AHGCharacter;
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

protected:
	virtual AHGCharacter* GetOwnerCharacter() const;
};
