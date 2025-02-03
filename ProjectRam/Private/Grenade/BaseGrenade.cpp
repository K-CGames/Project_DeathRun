// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade/BaseGrenade.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Character/WOICharacter.h"
#include "Component/CombatComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/ExplosionDamageInterface.h"
#include "DrawDebugHelpers.h"
#include "Perception/AISense_Hearing.h"

// Sets default values
ABaseGrenade::ABaseGrenade()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	GrenadeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GrenadeSphere"));
	SetRootComponent(GrenadeSphere);
	GrenadeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade"));
	GrenadeMesh->SetupAttachment(GrenadeSphere);
	ProjectileMovement->MaxSpeed = 1500.f;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->bShouldBounce = true;

}

// Called when the game starts or when spawned
void ABaseGrenade::BeginPlay()
{
	Super::BeginPlay();
	if (ProjectileMovement)
	{
		ProjectileMovement->OnProjectileBounce.AddDynamic(this, &ABaseGrenade::OnBounce);
	}
	StartDestroyTimer();
	SpawnTrailSystem();

}

void ABaseGrenade::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	if (BouncingSound)		//Add logic for not repeating sound effect
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			BouncingSound,
			GetActorLocation()
		);
	}
}

void ABaseGrenade::TraceForDamage()
{
	const FVector StartLocation = GetActorLocation();
	TArray <FHitResult> HitResults;
	TArray<AActor*> ActorToIgnore;
	const bool bHit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), StartLocation, StartLocation, MaxDamageRadius,
		UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorToIgnore, EDrawDebugTrace::None, HitResults, true);
	DrawDebugSphere(GetWorld(), GetActorLocation(), MaxDamageRadius, 32, FColor::Green, true);
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

void ABaseGrenade::DestroyTimerFinished()
{
	Destroy();
}

void ABaseGrenade::SpawnTrailSystem()
{
	if (TrailSystem)
	{
		TrailSystemComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			TrailSystem,
			GetRootComponent(),
			FName(),
			GetActorLocation(),
			GetActorRotation(),
			EAttachLocation::KeepWorldPosition,
			false
		);
	}
}

void ABaseGrenade::StartDestroyTimer()
{
	GetWorldTimerManager().SetTimer(
		DestroyTimer,
		this,
		&ThisClass::DestroyTimerFinished,
		DestroyTime
	);
}

void ABaseGrenade::Destroyed()
{
	Super::Destroyed();
	TraceForDamage();      	   
	FVector ActorLocation;
	ActorLocation.X = GetActorLocation().X;
	ActorLocation.Y = GetActorLocation().Y;
	ActorLocation.Z = GetActorLocation().Z + 100.f;
	if (Explosions)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Explosions, ActorLocation);
	}
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), 1.0f, this, 1.f);
}

// Called every frame
void ABaseGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
