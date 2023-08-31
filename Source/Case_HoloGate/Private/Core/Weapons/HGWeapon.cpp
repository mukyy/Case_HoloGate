// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Weapons/HGWeapon.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AHGWeapon::AHGWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetReplicates(true);
}
