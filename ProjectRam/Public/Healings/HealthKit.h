// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Healings/BaseHealing.h"
#include "HealthKit.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRAM_API AHealthKit : public ABaseHealing
{
	GENERATED_BODY()
public:
	AHealthKit();
protected:

	virtual void BeginPlay() override;

protected:

	void OnHealSphereOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& Hit) override;

	void OnHealSphereEndOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
};
