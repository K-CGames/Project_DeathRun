// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ProjectileWeapon/BaseProjectileWeapon.h"
#include "Weapon/ProjectileWeapon/BaseProjectileBulletActor.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


void ABaseProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);
	APawn* InsitgatorPawn = Cast<APawn>(GetOwner());
	const USkeletalMeshSocket* MuzzleSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	if (MuzzleSocket)
	{
		FTransform SocketTransform = MuzzleSocket->GetSocketTransform(GetWeaponMesh());
		FVector ToTarget = HitTarget - SocketTransform.GetLocation();
		//FVector ToTarget = HitTarget - BulletSocketTransform;
		FRotator TargetRotation = ToTarget.Rotation();
		if (ProjectileClass && InsitgatorPawn)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();
			SpawnParams.Instigator = InsitgatorPawn;

			UWorld* World = GetWorld();
			if (World )
			{
				World->SpawnActor<ABaseProjectileBulletActor>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
			}

		}
	}
}

void ABaseProjectileWeapon::DrawLineTrace()
{
	const USkeletalMeshSocket* MuzzleSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash"));
	FTransform SocketTransform = MuzzleSocket->GetSocketTransform(GetWeaponMesh());
	FHitResult HitResult;
	FVector Start = SocketTransform.GetLocation();
	FVector ShotDirection = SocketTransform.GetRotation().Vector();
	FVector End = Start + ShotDirection * 80000.f;
	FVector BeamEnd = End;
	if (GetWorld())
	{
		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_GameTraceChannel3);
		if (HitResult.bBlockingHit)
		{
			BeamEnd = HitResult.ImpactPoint;
		
		}
	}
}