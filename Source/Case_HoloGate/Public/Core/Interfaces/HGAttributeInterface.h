// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
};
