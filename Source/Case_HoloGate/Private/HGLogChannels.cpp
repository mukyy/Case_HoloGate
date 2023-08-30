// Fill out your copyright notice in the Description page of Project Settings.

#include "HGLogChannels.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY(LogHG);
DEFINE_LOG_CATEGORY(LogHGDebug);

void Error_MissingComponent(TSubclassOf<UActorComponent> ComponentClass)
{
	UE_LOG(LogHG, Error, TEXT("%s component is missing!"), *ComponentClass->GetDisplayNameText().ToString());
}