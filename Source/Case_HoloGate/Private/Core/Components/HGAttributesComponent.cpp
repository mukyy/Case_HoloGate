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

int32 UHGAttributesComponent::GetAttributeIndex(const FGameplayTag& Attribute) const
{
	const int32 attributeIndex  = Attributes.IndexOfByKey<FGameplayTag>(Attribute);

	if (attributeIndex == -1)
	{
		UE_LOG(LogHG, Warning, TEXT("Owner does not have %s attribute."), *Attribute.ToString());
		return -1.f;
	}
	return attributeIndex;
}

void UHGAttributesComponent::OnRep_Attributes_Implementation() const
{
}

void UHGAttributesComponent::Server_SetAttributeValue_Implementation(const FGameplayTag& Attribute, float NewValue)
{
	SetAttributeValue(Attribute, NewValue);
}

void UHGAttributesComponent::SetAttributeValue(const FGameplayTag& Attribute, float NewValue)
{
	if (GetOwnerRole() != ROLE_Authority)
	{
		Server_SetAttributeValue(Attribute, NewValue);
	}
	// Continues the flow for client as well so value changes are responsive.

	const int32 attributeIndex = GetAttributeIndex(Attribute);
	
	if (attributeIndex == -1)
	{
		return;
	}

	// TODO: Find a better flow.
	FAttribute& attributeRef = Attributes[attributeIndex];
	const float oldValue = attributeRef.Value;
	NewValue = FMath::Clamp(NewValue, attributeRef.MinMaxValue.X, attributeRef.MinMaxValue.Y);
	Attributes[attributeIndex].Value = NewValue;
	
	OnAttributeChanged.Broadcast(Attribute, oldValue, NewValue);

	// TODO: Not sure about this.
	// OnRep events are not fired on server so we force it if the we are on server side.
	if (GetOwnerRole() == ROLE_Authority)
	{
		OnRep_Attributes();
	}
}

void UHGAttributesComponent::ModifyAttribute(const FGameplayTag& Attribute, float Amount)
{
	const float modifiedValue = GetAttributeValue(Attribute) + Amount;
	SetAttributeValue(Attribute, modifiedValue);
}

float UHGAttributesComponent::GetAttributeValue(const FGameplayTag& Attribute) const
{
	const int32 attributeIndex = GetAttributeIndex(Attribute);

	// Avoid access to array if index is not found.
	if (attributeIndex == -1)
	{
		return -1;
	}
	
	return Attributes[attributeIndex].Value;
}
