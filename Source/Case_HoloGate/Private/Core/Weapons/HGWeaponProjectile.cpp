// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Weapons/HGWeaponProjectile.h"

#include "HGLogChannels.h"
#include "Core/Character/HGCharacter.h"
#include "Core/Components/HGAttributesComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AHGWeaponProjectile::AHGWeaponProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = 0.0f;
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

void AHGWeaponProjectile::SetDamage(float newValue)
{
	if (newValue <= 0.0f)
	{
		UE_LOG(LogHGDebug, Warning, TEXT("Attempted to set projectile damage with negative value!"));
		return;
	}
	Damage = newValue;
}

void AHGWeaponProjectile::ProjectileSpawned(FVector projectileVelocity)
{
	GetProjectileMovement()->SetVelocityInLocalSpace(projectileVelocity);
}

void AHGWeaponProjectile::Explode()
{
	FCollisionShape sphereShape = FCollisionShape::MakeSphere(100.0f);

	// Open comment to debug area.
	//DrawDebugSphere(GetWorld(), GetActorLocation(), sphereShape.GetSphereRadius(), 50, FColor::Purple, false, 2.0f);

	TArray<FOverlapResult> outHits;
	//TODO: make a seperate trace channel for damage traces.
	FCollisionQueryParams collisionQuery;
	collisionQuery.AddIgnoredActor(GetInstigator());
	// check if something got hit in the sweep
	bool isHit = GetWorld()->OverlapMultiByChannel(outHits, GetActorLocation(), FQuat::Identity, ECC_Visibility, sphereShape, collisionQuery);
	for (FOverlapResult hit : outHits)
	{
		AHGCharacter* hitCharacter = Cast<AHGCharacter>(hit.GetActor());
		if (IsValid(hitCharacter))
		{
			//TODO: Cache gameplay tags to c++
			hitCharacter->GetAttributesComponent()->ModifyAttribute(FGameplayTag::RequestGameplayTag("Attribute.Health"), -GetDamage());
		}
	}
	OnProjectileExploded.Broadcast(outHits);
	
	Destroy();
}

