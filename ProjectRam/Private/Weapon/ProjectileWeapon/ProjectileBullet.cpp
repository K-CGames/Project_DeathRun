// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ProjectileWeapon/ProjectileBullet.h"
#include "Interfaces/BulletHitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

void AProjectileBullet::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Hit.GetActor())
	{
		auto ownerCharacter = Cast<ACharacter>(GetOwner());
		auto InstigatorController = ownerCharacter->GetController();
		//IBulletHitInterface* BulletHit = Cast<IBulletHitInterface>(Hit.GetActor());
		bool bImplementsInterfaces = Hit.GetActor()->Implements<UBulletHitInterface>();
		if (bImplementsInterfaces && (Hit.GetActor()->Tags != GetOwner()->Tags))
		{
			IBulletHitInterface::Execute_BulletHit(Hit.GetActor(), Hit);
			IBulletHitInterface::Execute_ApplyBulletDamage(Hit.GetActor(), Hit, InstigatorController, this, headDamage, bodyDamage);
		}
	}
	Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}