// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Weapons/HGWeaponProjectile.h"

#include "HGLogChannels.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AHGWeaponProjectile::AHGWeaponProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AHGWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


UProjectileMovementComponent* AHGWeaponProjectile::GetProjectileMovement() const
{
	if (ProjectileMovement == nullptr)
	{
		Error_MissingComponent(GetClass());
		return nullptr;
	}
	
	return ProjectileMovement;
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

void AHGWeaponProjectile::ProjectileSpawned(FVector ProjectileVelocity)
{
	GetProjectileMovement()->SetVelocityInLocalSpace(ProjectileVelocity);
}

