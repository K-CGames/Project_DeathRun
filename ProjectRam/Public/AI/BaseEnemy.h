// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/BulletHitInterface.h"
#include "Interfaces/AIFunctionInterface.h"
#include "Interfaces/AimAssistInterface.h"
#include "Interfaces/ExplosionDamageInterface.h"
#include "BaseEnemy.generated.h"

UCLASS()
class PROJECTRAM_API ABaseEnemy : public ACharacter, public IBulletHitInterface, public IAIFunctionInterface, public IExplosionDamageInterface,public IAimAssistInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	UFUNCTION(BlueprintCallable)
		void StoreHitNumber(UUserWidget* HitNumber, FVector Location);
	UFUNCTION()
		void DestroyHitNumber(UUserWidget* HitNumber);
	void UpdateHitNumber();
	void Death();
	UPROPERTY(EditAnywhere, Category = Type)
		bool bIsGuard = false;
	UPROPERTY(VisibleAnywhere)
		int32 MaxAmmoCount = 512;
	UFUNCTION(BlueprintCallable)
		void ReloadWeapon();
private:
	UPROPERTY(VisibleAnywhere)
		TMap<UUserWidget*, FVector> HitNumbers;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), BlueprintReadWrite)
		float HitNumberDestroyTime = 1.f;
	UPROPERTY(EditAnywhere, Category = Weapons, meta = (AlloprivateAccess = true))
		TSubclassOf<class ABaseWeapon> DefaultWeapon;
	UPROPERTY()
		ABaseWeapon* StartingWeapon = nullptr;
	UPROPERTY(BlueprintReadOnly, Category = TeamID, meta = (AllowPrivateAccess = true))
		int32 MyTeamID = 1; //1 is for Enemies;
	UPROPERTY(VisibleAnywhere, Category = "Health")
		float CurrentHealth = 100.f;
	bool bIsDead = false;
	FTimerHandle DeathTimer;
	void DestroyMeshTimer();
	void EquipWeapon(ABaseWeapon* WeaponToEquip, AActor* NewOwner, APawn* NewInstigator);

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), BlueprintReadWrite, Category = BehaviorTree)
		class UBehaviorTree* AIBehavior;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), BlueprintReadWrite, Category = BehaviorTree)
		class UBlackboardComponent* BlackBoardAI;

protected:
	//Interfaces
	virtual void BulletHit_Implementation(FHitResult HitResult) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamagerCauser) override;
	virtual void  ApplyBulletDamage_Implementation(FHitResult HitResult, AController* InstigatorController, AActor* DamagerCauser, float headDamage, float bodyDamage) override;
	void ApplyExplosionDamage_Implementation(float BaseDamage,
		float MinimumDamage, const FVector& Origin, float DamageInnerRadius,
		float DamageOuterRadius, float DamageFallOf, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent)
		void FireWeapon(); //This function sets the Overlay to Aim and then shoot
	virtual void StartFiring_Implementation(bool bToggleFire) override;
	UFUNCTION(BlueprintCallable)
		void SpawnDefaultWeapon();
	bool bCanFire = true;
	FTimerHandle FireTimer;
	void AutoFire();
	UPROPERTY(EditAnywhere, Category = Weapon)
		float ItemTraceLength = 60000.f;
	void LineTraceToPlayer();
	UPROPERTY()
		FVector HitVector = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = Reload)
		class  UAnimMontage* ReloadMontage;
	UFUNCTION(BlueprintCallable)
		void FinishReloading();

public:
	UFUNCTION(BlueprintImplementableEvent)
		void ShowHitNumber(int32 Damage, FVector HitLocation, bool bIsHeadShot);
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool IsEnemyDead();
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE bool GetIsGuard() const { return bIsGuard; }
};
