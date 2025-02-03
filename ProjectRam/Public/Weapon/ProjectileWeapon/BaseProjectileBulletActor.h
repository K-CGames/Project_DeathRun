// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectileBulletActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledBulletActorDespawn, ABaseProjectileBulletActor*, BulletActor);

UCLASS()
class PROJECTRAM_API ABaseProjectileBulletActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectileBulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UFUNCTION()
		virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		float Damage = 20.f;
	UPROPERTY(EditAnywhere)
		float HeadShotDamage = 50.f;
protected:

	void DestroyTimerFinished();
	void SpawnTrailSystem();
	virtual void Destroyed() override;
	void StartDestroyTimer();
protected:
	UPROPERTY(EditAnywhere)
		class USphereComponent* BulletCollision;
	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, Category = VFX)
		class UParticleSystem* Tracer;

	class UParticleSystemComponent* TracerComponent;
	UPROPERTY(EditAnywhere, Category = VFX)
		UParticleSystem* ImpactParticle;
	UPROPERTY(EditAnywhere, Category = VFX)
		UParticleSystem* GroundParticle;
	UPROPERTY(EditAnywhere, Category = VFX)
		class USoundCue* ImpactSound;
	class ABaseWeapon* WeaponEquipped;
	UPROPERTY(EditAnyWhere, Category = VFX)
		class UNiagaraSystem* TrailSystem;
	UPROPERTY()
		class UNiagaraComponent* TrailSystemComp;
	FTimerHandle DestroyTimer;
	UPROPERTY(EditAnywhere, Category = VFX)
		float DestroyTime = 3.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float GetDamageofBullet() const;
	float GetHeadShotDamageofBullet() const;
	UFUNCTION(BlueprintCallable)
		void Deactivate();
	void SetActive(bool bIsActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int32 Index);

	bool IsActive();
	int32 GetPoolIndex();
	bool Active = false;
	int32 PoolIndex;
	FOnPooledBulletActorDespawn BulletActorDespawn;

};
