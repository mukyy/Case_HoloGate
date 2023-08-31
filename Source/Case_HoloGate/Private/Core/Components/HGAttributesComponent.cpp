// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/HGAttributesComponent.h"

#include "HGLogChannels.h"
#include "Net/UnrealNetwork.h"


UHGAttributesComponent::UHGAttributesComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
}

void UHGAttributesComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHGAttributesComponent, Attributes);
}

int32 UHGAttributesComponent::GetAttributeIndex(const FGameplayTag& attribute) const
{
	const int32 attributeIndex  = Attributes.IndexOfByKey<FGameplayTag>(attribute);

	if (attributeIndex == -1)
	{
		UE_LOG(LogHGDebug, Display, TEXT("%s actor does not have %s attribute"), *GetOwner()->GetName(), *attribute.ToString())
		return -1.f;
	}
	return attributeIndex;
}


void UHGAttributesComponent::Server_SetAttributeValue_Implementation(const FGameplayTag& attribute, float newValue)
{
	SetAttributeValue(attribute, newValue);
}

void UHGAttributesComponent::SetAttributeValue(const FGameplayTag& attribute, float newValue)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		Server_SetAttributeValue(attribute, newValue);
	}
	// Continues the flow for client as well so value changes are responsive.

	const int32 attributeIndex = GetAttributeIndex(attribute);
	
	if (attributeIndex == -1)
	{
		return;
	}

	// TODO: Find a better flow.
	FAttribute& attributeRef = Attributes[attributeIndex];
	const float oldValue = attributeRef.Value;
	newValue = FMath::Clamp(newValue, attributeRef.MinMaxValue.X, attributeRef.MinMaxValue.Y);
	Attributes[attributeIndex].Value = newValue;
	
	OnAttributeChanged.Broadcast(attribute, oldValue, newValue);

}

void UHGAttributesComponent::ModifyAttribute(const FGameplayTag& attribute, float amount)
{
	const float modifiedValue = GetAttribute(attribute).Value + amount;
	SetAttributeValue(attribute, modifiedValue);
}

void UHGAttributesComponent::ForceBroadcastAttributes()
{
	for (FAttribute attribute : Attributes)
	{
		OnAttributeChanged.Broadcast(attribute.AttributeTag, attribute.Value, attribute.Value);
	}
}

FAttribute UHGAttributesComponent::GetAttribute(const FGameplayTag& attribute) const
{
	const int32 attributeIndex = GetAttributeIndex(attribute);

	// Avoid access to array if index is not found.
	if (attributeIndex == -1)
	{
		return FAttribute();
	}
	
	return Attributes[attributeIndex];
}

