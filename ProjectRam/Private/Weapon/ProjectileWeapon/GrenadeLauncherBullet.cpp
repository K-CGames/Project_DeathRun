// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ProjectileWeapon/GrenadeLauncherBullet.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/ExplosionDamageInterface.h"

AGrenadeLauncherBullet::AGrenadeLauncherBullet()
{
	ProjectileMovement->bShouldBounce = true;
}

void AGrenadeLauncherBullet::BeginPlay()
{
	Super::BeginPlay();
	SpawnTrailSystem();
	StartDestroyTimer();
	ProjectileMovement->OnProjectileBounce.AddDynamic(this, &ThisClass::OnBounce);
}

void AGrenadeLauncherBullet::Destroyed()
{
	Super::Destroyed();
	Destroy();
	TraceForDamage();
}

void AGrenadeLauncherBullet::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (BouncingSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			BouncingSound,
			GetActorLocation()
		);
	}
}

void AGrenadeLauncherBullet::TraceForDamage()
{
	const FVector StartLocation = GetActorLocation();
	TArray <FHitResult> HitResults;
	TArray<AActor*> ActorToIgnore;
	const bool bHit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartLocation, StartLocation, MaxDamageRadius,
		UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorToIgnore, EDrawDebugTrace::None, HitResults, true);
	if (bHit)
	{
		for (auto& Hit : HitResults)
		{
			bool bImplementsInterface = Hit.GetActor()->Implements<UExplosionDamageInterface>();
			if (bImplementsInterface)
			{
				IExplosionDamageInterface::Execute_ApplyExplosionDamage(Hit.GetActor(), BaseDamage,
					MinDamage, GetActorLocation(), MinDamageRadius, MaxDamageRadius, DamageFallof, this);
			}
		}
	}
}
