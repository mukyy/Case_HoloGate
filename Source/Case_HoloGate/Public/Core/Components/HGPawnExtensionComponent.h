// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/HGComponent.h"
#include "Core/Interfaces/HGAttributeInterface.h"
#include "HGPawnExtensionComponent.generated.h"

class UHGAttributesComponent;
class UHGPawnComponent;

/**  
 * HGPawnExtensionComponent
 *
 *  Handles communication between other components.
 *  Contains event dispatchers for interface calls, which then can be listened from other classes to execute component functionality.
 *  Purpose of this component is to allow components to be modular so dependencies are as minimum as possible.
 */
UCLASS(Blueprintable, Config = Game, Meta = (ShortTooltip = "Controls and manages other components related to Pawn."))
class CASE_HOLOGATE_API UHGPawnExtensionComponent : public UHGComponent, public IHGAttributeInterface
{
	GENERATED_BODY()
public:
	UHGPawnExtensionComponent();
	
protected:
	UFUNCTION(BlueprintCallable)
	UHGAttributesComponent* GetAttributesComponent() const;
	
public:
#pragma region AttributeInterface
	virtual float GetAttribute(const FGameplayTag& Attribute) const override;
	virtual void SetAttribute(const FGameplayTag& Attribute, float NewValue) const override;
	virtual void ModifyAttribute(const FGameplayTag& Attribute, float Amount) const override;

#pragma endregion AttributeInterface
};
