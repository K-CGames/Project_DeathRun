// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/ProjectileWeapon/BaseProjectileWeapon.h"
#include "SniperRifle.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRAM_API ASniperRifle : public ABaseProjectileWeapon
{
	GENERATED_BODY()
public:
	ASniperRifle();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UCameraComponent* ScopeCamera;
	FORCEINLINE UCameraComponent* GetScopeCamera() const { return ScopeCamera; }
};
