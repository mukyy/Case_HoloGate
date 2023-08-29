// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Core/Components/HGComponent.h"
#include "HGAttributesComponent.generated.h"

USTRUCT(Blueprintable)
struct FAttribute
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta = (Categories = "Attribute"))
	FGameplayTag AttributeTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DefaultValue = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D DefaultMinMaxValue = FVector2D(0.0, 100.0f);

	// Attribute tag is used for keying when used in Arrays.
	bool operator==(const FGameplayTag& Other) const
	{
		return AttributeTag.MatchesTagExact(Other);
	}
};

/**
 * UHGAttributesComponent
 *
 *  Manages stats of the owner that are primitive and numeric. e.g: Health, Mana, Stamina
 *  Dynamically creates and handles replication of the attributes.
 */
UCLASS(Blueprintable, Meta = (ShortTooltip = "Manages attributes of any actor its attached to."))
class CASE_HOLOGATE_API UHGAttributesComponent : public UHGComponent
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAttribute> OwnedAttributes;

	// Finds index of the FAttribute struct inside OwnedAttributes using Attribute`s tag.
	UFUNCTION(BlueprintCallable)
	int32 FindAttributeIndex(const FGameplayTag& Attribute);
	
};
