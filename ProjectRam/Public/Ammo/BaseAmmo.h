// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponTypes.h"
#include "BaseAmmo.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class USoundCue;

UCLASS()
class PROJECTRAM_API ABaseAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ItemMesh;
	UPROPERTY(EditAnywhere)
		USphereComponent* ItemSphere;
	UPROPERTY(EditAnywhere, Category = Name)
		FName ItemName;
	UPROPERTY(EditAnywhere, Category = Sound)
		USoundCue* PickupSound;
	UFUNCTION()

		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& Hit);
protected:
	EAmmoType AmmoType;
	int32 minAmmoRange;
	int32 maxAmmoRange;
};
