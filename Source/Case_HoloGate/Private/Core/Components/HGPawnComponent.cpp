// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Components/HGPawnComponent.h"

#include "HGLogChannels.h"
#include "Core/Character/HGCharacter.h"

AHGCharacter* UHGPawnComponent::GetOwnerCharacter() const
{
	AHGCharacter* ownerCharacter = Cast<AHGCharacter>(GetOwner());
	if (!IsValid(ownerCharacter))
	{
		UE_LOG(LogHG, Error, TEXT("%s components owner is not of AHGCharacter type!"), *GetName());
		return nullptr;
	}

	return ownerCharacter;
}
