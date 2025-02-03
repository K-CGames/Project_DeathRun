// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseHealing.generated.h"

UCLASS()
class PROJECTRAM_API ABaseHealing : public AActor
{
	GENERATED_BODY()
	

public:
	// Sets default values for this actor's properties
	ABaseHealing();

protected:
	UPROPERTY()
		FName HealName;
	UPROPERTY()
		float AmountToHeal;
	UPROPERTY()
		float ShieldToHeal;
protected:
	UPROPERTY(VisibleAnywhere)
		class USphereComponent* HealSphere;
	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* HealItem;
	UPROPERTY(EditAnywhere)
		class UWidgetComponent* HealWidget;
protected:
	UFUNCTION()
		virtual void OnHealSphereOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& Hit) PURE_VIRTUAL(ABaseHealing::OnHealSphereOverlap, );
	UFUNCTION()
		virtual void OnHealSphereEndOverlap(UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex)PURE_VIRTUAL(ABaseHealing::OnHealSphereEndOverlap, );
public:
	FORCEINLINE FName GetHealingName() const { return HealName; }

};
