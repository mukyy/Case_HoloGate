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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AttributeTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Value = 1.0f;

	// Limits the value between this values when modified.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D MinMaxValue = FVector2D(0.0, 100.0f);

	// AttributeTag is used for keying when used in Arrays.
	bool operator==(const FGameplayTag& Other) const
	{
		return AttributeTag.MatchesTagExact(Other);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayTag, Attribute, float , OldValue, float, NewValue);

/**
 * UHGAttributesComponent
 *
 *  Manages stats of the owner that are primitive and numeric. e.g: Health, Mana, Stamina
 *  Dynamically creates and handles replication of the attributes.
 */
UCLASS(Meta = (ShortTooltip = "Manages attributes of any actor its attached to."))
class CASE_HOLOGATE_API UHGAttributesComponent : public UHGComponent
{
	GENERATED_BODY()
public:
	UHGAttributesComponent();

private:
	UFUNCTION(Server, Reliable)
	void Server_SetAttributeValue(const FGameplayTag& attribute, float newValue);
	
protected:
	// Finds index of the FAttribute struct inside OwnedAttributes using Attribute`s tag.
	UFUNCTION(BlueprintCallable)
	int32 GetAttributeIndex(const FGameplayTag& attribute) const;
	
	UPROPERTY(Replicated, EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAttribute> Attributes;
	
public:
	// Calls OnAttributeChanged event on all attributes to notify listeners at once.
	UFUNCTION(BlueprintCallable)
	void ForceBroadcastAttributes();

	UFUNCTION(BlueprintCallable)
	FAttribute GetAttribute(const FGameplayTag& attribute) const;

	UFUNCTION(BlueprintCallable)
	void SetAttributeValue(const FGameplayTag& attribute, float newValue);

	// Can be used to send raw modifying amount which then gets added to attribute for result. e.g: Value + Amount. Amount can be both negative and positive, negative acts as a damage and positive as restoration.
	UFUNCTION(BlueprintCallable)
	void ModifyAttribute(const FGameplayTag& attribute, float amount);

	// Listen for this for attribute change events.
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChanged OnAttributeChanged;
	
};

