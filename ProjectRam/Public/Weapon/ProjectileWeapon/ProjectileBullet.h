// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ProjectileWeapon/BaseProjectileBulletActor.h"
#include "ProjectileBullet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRAM_API AProjectileBullet : public ABaseProjectileBulletActor
{
	GENERATED_BODY()
protected:
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit) override;
	UPROPERTY(EditAnywhere, Category = Damage)
		float bodyDamage = 10.f;
	UPROPERTY(EditAnywhere, Category = Damage)
		float headDamage = 20.f;
};
