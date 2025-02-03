// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "HitScanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRAM_API AHitScanWeapon : public ABaseWeapon
{
	GENERATED_BODY()
protected:

	AHitScanWeapon();
	virtual void Fire(const FVector& HitTarget) override;
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = CrosshairAdjusment)
		float XDirection = 5.f;
	UPROPERTY(EditAnywhere, Category = CrosshairAdjusment)
		float YDirection = 5.f;
	UPROPERTY(EditAnywhere, Category = CrosshairAdjusment)
		float ZDirection = 5.f;
	UPROPERTY(EditAnywhere, Category = Weapon)
		float WeaponRange = 80000.f; //10mts
	UPROPERTY(EditAnywhere, Category = Weapon)
		float BulletSpread = 5.f;
	UPROPERTY(EditAnywhere, Category = Weapon)
		float bodyDamage = 10.f;
	UPROPERTY(EditAnywhere, Category = Weapon)
		float headDamage = 20.f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = Weapon)
		class UParticleSystem* BeamParticles;
	UPROPERTY(EditAnywhere, Category = Sounds)
		class USoundCue* WhooshSound;	
};
