// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/HitScanWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Kismet/KismetMathLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Interfaces/BulletHitInterface.h"
#include "GameFramework/Character.h"

AHitScanWeapon::AHitScanWeapon()
{
	AmmoTypeForWeapon = EAmmoType::EAT_MediumAmmo;
}

void AHitScanWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	check(OwnerPawn != nullptr);
	auto InstigatorController = OwnerPawn->GetController();
	const USkeletalMeshSocket* MuzzleSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	FVector2D ViewportSize;
	if (GEngine)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	if (MuzzleSocket && OwnerPawn)
	{
		UWorld* World = GetWorld();
		FTransform SocketTransform = MuzzleSocket->GetSocketTransform(GetWeaponMesh());
		FHitResult HitResult;
		FVector Start = SocketTransform.GetLocation();
		FVector ShotDirection = SocketTransform.GetRotation().Vector();
		FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(WeaponTrace), false, this);
		float HalfRad = FMath::DegreesToRadians(BulletSpread);
		ShotDirection = FMath::VRandCone(ShotDirection, HalfRad, HalfRad); //for spreading bullets
		FVector End = Start + (ShotDirection)*WeaponRange;
		FVector BeamEnd = End;
		ACharacter* HeroActor = UGameplayStatics::GetPlayerCharacter(World, 0);
		if (World)
		{
			bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel3, QueryParams);
			if (bHit)
			{
				if (HitResult.bBlockingHit)
				{
					BeamEnd = HitResult.ImpactPoint;
					IBulletHitInterface* BulletHit = Cast<IBulletHitInterface>(HitResult.GetActor());
					bool bImplementsInterfaces = HitResult.GetActor()->Implements<UBulletHitInterface>();
					//if (BulletHit)
					//{
					//	if (HitResult.GetActor()->Tags != GetOwner()->Tags)
					//	{
					//		BulletHit->BulletHit_Implementation(HitResult);
					//		BulletHit->ApplyBulletDamage_Implementation(HitResult, InstigatorController, this, headDamage, bodyDamage);   //Change this
					//	}

					//}
					if (bImplementsInterfaces)
					{
						if (HitResult.GetActor()->Tags != GetOwner()->Tags)
						{
							IBulletHitInterface::Execute_ApplyBulletDamage(HitResult.GetActor(), HitResult, InstigatorController, this, headDamage, bodyDamage);
						}
					}

				}
				if (ImpactSound)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.ImpactPoint);
				}
			}

			if (BeamParticles)
			{
				UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(
					World,
					BeamParticles,
					Start,
					FRotator::ZeroRotator,
					true, EPSCPoolMethod::AutoRelease
				);
				//Beam->ReleaseToPool();
				FWorldPSCPool Pool;

				//UParticleSystemComponent* Beam = Pool.CreateWorldParticleSystem(BeamParticles, GetWorld(), EPSCPoolMethod::ManualRelease_OnComplete);
				if (Beam)
				{
					Beam->SetVectorParameter(FName("Target"), BeamEnd); //Target is present inside the beam particle system we can access
					//Beam->ReleaseToPool();
					//Pool.ReclaimWorldParticleSystem(Beam);
					UE_LOG(LogTemp, Warning, TEXT("Reclaimed to WorldPatuclesSyetme"));
				}
			}


		}
	}
}

void AHitScanWeapon::BeginPlay()
{
	Super::BeginPlay();

	//if (BeamParticles)
	//{
	//	for (int i = 0; i < 32; i++)
	//	{
	//		UParticleSystemComponent* Beam = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BeamParticles, FVector::ZeroVector, FRotator::ZeroRotator, true, EPSCPoolMethod::FreeInPool);
	//		//Beam->ReleaseToPool();
	//	}
	//}

}