// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "BaseProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRAM_API ABaseProjectileWeapon : public ABaseWeapon
{
	GENERATED_BODY()		 
public:

	virtual void Fire(const FVector& HitTarget) override;
	 
	void DrawLineTrace();

private:
	UPROPERTY(EditAnywhere, Category = BulletInfo)
		TSubclassOf<class ABaseProjectileBulletActor> ProjectileClass;
	UPROPERTY(EditAnywhere, Category = BulletInfo)
		float BulletSpread = 10.f;
	FTimerHandle DestroyBullet;
	
};
