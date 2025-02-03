// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGrenade.generated.h"

UCLASS()
class PROJECTRAM_API ABaseGrenade : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABaseGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

	void TraceForDamage();
	void DestroyTimerFinished();
	void SpawnTrailSystem();
	void StartDestroyTimer();
	virtual void Destroyed() override;
private:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* GrenadeMesh;	    //Change to InstanceStaticMesh
	UPROPERTY(EditAnywhere)
		class USphereComponent* GrenadeSphere;
	UPROPERTY(EditAnyWhere)
		class UNiagaraSystem* TrailSystem;
	UPROPERTY(EditAnywhere)
	UNiagaraSystem* Explosions;
	UPROPERTY()
		class UNiagaraComponent* TrailSystemComp;
	FTimerHandle DestroyTimer;
	UPROPERTY(EditAnywhere)
		float DestroyTime = 2.f;
	UPROPERTY(EditAnywhere)
		float MaxDamageRadius = 800.f;
	UPROPERTY(EditAnywhere)
		UParticleSystem* ImpactParticle;
	UPROPERTY(EditAnywhere)
		class USoundCue* ImpactSound;
	UPROPERTY(EditAnywhere)
		class USoundCue* BouncingSound;
	UPROPERTY(EditAnywhere, Category = Damage)
		float BaseDamage = 120.f;
	UPROPERTY(EditAnywhere, Category = Damage)
		float MinDamage = 20.f;
	UPROPERTY(EditAnywhere, Category = Damage)
		float MinDamageRadius = 10.f;
	UPROPERTY(EditAnywhere, Category = Damage)
		float DamageFallof = .5f;
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	FORCEINLINE UStaticMeshComponent* GetGrenadeMesh() const { return GrenadeMesh; }
	UFUNCTION(BlueprintCallable)
		FORCEINLINE USphereComponent* GetGrenadeSphere() const { return GrenadeSphere; }
};
