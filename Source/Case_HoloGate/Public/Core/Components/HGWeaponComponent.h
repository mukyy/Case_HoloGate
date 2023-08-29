// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/HGPawnComponent.h"
#include "HGWeaponComponent.generated.h"

/**
 * UHGWeaponComponent
 *
 *  Handles gameplay functionality of the weapons such as firing, reloading etc.
 *  Gets added runtime when a weapon is equipped.
 */
UCLASS(Blueprintable)
class CASE_HOLOGATE_API UHGWeaponComponent : public UHGPawnComponent
{
	GENERATED_BODY()
	
};
