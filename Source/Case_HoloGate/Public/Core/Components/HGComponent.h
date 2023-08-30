// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HGComponent.generated.h"

/**
 * UHGComponent
 *
 *  Base component that all components should be deriving from for extendability. 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Meta = (ShortTooltip = "Base actor component used in this project.") )
class CASE_HOLOGATE_API UHGComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHGComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;
		
};
