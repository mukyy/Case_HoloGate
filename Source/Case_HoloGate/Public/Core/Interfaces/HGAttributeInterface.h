// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "HGAttributeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHGAttributeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * IHGAttributeInterface
 *
 *  Manages attribute getters & setters.
 *  Used to protect AttributesComponent from direct access.
 */
class CASE_HOLOGATE_API IHGAttributeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAttribute(const FGameplayTag& Attribute) const = 0;
	virtual void SetAttribute(const FGameplayTag& Attribute, float NewValue) const = 0;

	// Instead of setting the value directly, calculates new value using (Value + Amount). Amount can be negative as well.
	virtual void ModifyAttribute(const FGameplayTag& Attribute, float Amount) const = 0;

};
