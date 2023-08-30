// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Weapons/HGWeaponProjectile.h"

#include "HGLogChannels.h"


// Sets default values
AHGWeaponProjectile::AHGWeaponProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHGWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

float AHGWeaponProjectile::GetDamage() const
{
	return Damage;
}

void AHGWeaponProjectile::SetDamage(float NewValue)
{
	if (NewValue <= 0.0f)
	{
		UE_LOG(LogHGDebug, Warning, TEXT("Attempted to set projectile damage with negative value!"));
		return;
	}
	Damage = NewValue;
}

// Called every frame
void AHGWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

