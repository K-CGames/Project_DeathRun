// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ExplosionDamageInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UExplosionDamageInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTRAM_API IExplosionDamageInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ApplyExplosionDamage(float BaseDamage,
			float MinimumDamage, const FVector& Origin, float DamageInnerRadius,
			float DamageOuterRadius, float DamageFallOf, AActor* DamageCauser);
};
