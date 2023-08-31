// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Logging/LogMacros.h"

class UObject;

/**
 *  Use project specific log channels so future issues can be filtered out easier.
 */

CASE_HOLOGATE_API DECLARE_LOG_CATEGORY_EXTERN(LogHG, Log, All);
CASE_HOLOGATE_API DECLARE_LOG_CATEGORY_EXTERN(LogHGDebug, Log, All);

CASE_HOLOGATE_API void Error_MissingComponent(TSubclassOf<UActorComponent> componentClass);