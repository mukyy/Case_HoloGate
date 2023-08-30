// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HGComponent.generated.h"

/**
 * UHGComponent
 *
 *  Base abstract component that all components should be deriving from for extendability. 
 */
UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Meta = (ShortTooltip = "Base abstract actor component to derive from.") )
class CASE_HOLOGATE_API UHGComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHGComponent();

};
