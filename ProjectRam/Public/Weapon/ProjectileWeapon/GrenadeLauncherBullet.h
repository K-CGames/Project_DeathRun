// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ProjectileWeapon/ProjectileBullet.h"
#include "GrenadeLauncherBullet.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRAM_API AGrenadeLauncherBullet : public AProjectileBullet
{
	GENERATED_BODY()
public:
	AGrenadeLauncherBullet();
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	UFUNCTION()
		void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);
	void TraceForDamage();
	UPROPERTY(EditAnywhere)
		float MaxDamageRadius = 800.f;
	UPROPERTY(EditAnywhere, Category = Damage)
		float BaseDamage = 120.f;
	UPROPERTY(EditAnywhere, Category = Damage)
		float MinDamage = 20.f;
	UPROPERTY(EditAnywhere, Category = Damage)
		float MinDamageRadius = 10.f;
	UPROPERTY(EditAnywhere, Category = Damage)
		float DamageFallof = .5f;
private:
	UPROPERTY(EditAnywhere, Category = Sounds)
		class USoundCue* BouncingSound;
};
