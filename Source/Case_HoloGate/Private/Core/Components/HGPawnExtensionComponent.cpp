// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/HGPawnExtensionComponent.h"

#include "HGLogChannels.h"
#include "Core/Components/HGAttributesComponent.h"

UHGPawnExtensionComponent::UHGPawnExtensionComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.bCanEverTick = false;

    SetIsReplicatedByDefault(true);

}

UHGAttributesComponent* UHGPawnExtensionComponent::GetAttributesComponent() const
{
	UHGAttributesComponent* attributesComponent = GetOwner()->GetComponentByClass<UHGAttributesComponent>();
	if (attributesComponent == nullptr)
	{
		UE_LOG(LogHG, Error, TEXT("Attributes Component is missing!"));
	}
	return attributesComponent;
}

float UHGPawnExtensionComponent::GetAttribute(const FGameplayTag& Attribute) const
{
	return GetAttributesComponent()->GetAttributeValue(Attribute);
}

void UHGPawnExtensionComponent::SetAttribute(const FGameplayTag& Attribute, float NewValue) const
{
	GetAttributesComponent()->SetAttributeValue(Attribute, NewValue);
}

void UHGPawnExtensionComponent::ModifyAttribute(const FGameplayTag& Attribute, float Amount) const
{
	GetAttributesComponent()->ModifyAttribute(Attribute, Amount);
}
