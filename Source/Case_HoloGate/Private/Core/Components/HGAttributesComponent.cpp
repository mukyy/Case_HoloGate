// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/HGAttributesComponent.h"

int32 UHGAttributesComponent::FindAttributeIndex(const FGameplayTag& Attribute)
{
	return OwnedAttributes.IndexOfByKey<FGameplayTag>(Attribute);
}
