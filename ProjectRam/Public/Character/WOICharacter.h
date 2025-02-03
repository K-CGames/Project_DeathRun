// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AISightTargetInterface.h"
#include "Interfaces/PickupInterface.h"
#include "Interfaces/BulletHitInterface.h"
#include "Interfaces/ExplosionDamageInterface.h"
#include "WeaponTypes.h"
#include "WOICharacter.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UCombatComponent;
class UCameraComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;
class UAnimMontage;
class USplineComponent;
class ABaseWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEquipItemDelegate, int32, CurrentSlotIndex, int32, NewSlotIndex);

UCLASS()
class PROJECTRAM_API AWOICharacter : public ACharacter, public IAISightTargetInterface, public IPickupInterface, public IBulletHitInterface, public IExplosionDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWOICharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;
	/**
	* To access our created ActorComponents at the earliest
	*/
	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(BlueprintAssignable, meta = (AllowPrivateAccess = true))
		FEquipItemDelegate ItemDelegate;
protected:
	void SetRunning(bool bNewRunning);
	void SetAiming(bool bNewTargeting);
	void InterpFOV(float DeltaTime);
	void SpawnDefaultWeapon();
	void SpawnSecondaryWeapon();
protected:
	///**
	//* Movement related Functions
	//*/
	UFUNCTION(BlueprintCallable)
		void Turn(float Value);
	UFUNCTION(BlueprintCallable)
		void LookUp(float Value);
	UFUNCTION(BlueprintCallable)
		void MoveFoward(float Value);
	UFUNCTION(BlueprintCallable)
		void MoveRight(float Value);
	UFUNCTION(BlueprintCallable)
		void Sprint();
	UFUNCTION(BlueprintCallable)
		void StopSprint();
	UFUNCTION(BlueprintCallable)
		void Jumping();
	UFUNCTION(BlueprintCallable)
		void StopJump();
	UFUNCTION(BlueprintCallable)
		void StartCrouch();
	UFUNCTION(BlueprintCallable)
		void EquipButtonPressed();
	UFUNCTION(BlueprintCallable)
		void EquipPrimaryWeaponButtonPressed();
	UFUNCTION(BlueprintCallable)
		void EquipSecondaryWeaponButtonPressed();
	UFUNCTION(BlueprintCallable)
		void AimButtonPressed();
	UFUNCTION(BlueprintCallable)
		void AimButtonReleased();
	UFUNCTION(BlueprintCallable)
		void OnStartFire();
	UFUNCTION(BlueprintCallable)
		void OnStopFire();
	UFUNCTION(BlueprintCallable)
		void Reload();
	UFUNCTION(BlueprintCallable)
		void GrenadeButtonPressed();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
		void DrainStamina();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
		void RegenerateStamina();
	void StartWeaponFire();
	void StopWeaponFire();
	void SetCharacterSpeed(float NewSpeedValue);
	UFUNCTION(BlueprintImplementableEvent, meta = (AllowPrivateAccess = true))
		void AddSplineMeshs();
	UFUNCTION(BlueprintImplementableEvent, meta = (AllowPrivateAccess = true))
		void ClearArc();
	UFUNCTION(BlueprintImplementableEvent)
		void GrenadePrediction();
private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = true), Category = WeaponType, BlueprintReadWrite)
		UCombatComponent* CombatComp;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = Movement, BlueprintReadOnly)
		UCameraComponent* WOICamera;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = Movement, BlueprintReadOnly)
		USkeletalMeshComponent* Mesh1P;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = Movement, BlueprintReadOnly)
		UStaticMeshComponent* GrenadeMesh;

protected:
	//Interfaces implementation;
	virtual void AmmoPickup_Implementation(EAmmoType AmmoType, int32 AmountToPickup) override;
	virtual void ApplyBulletDamage_Implementation(FHitResult HitResult, AController* InstigatorController, AActor* DamagerCauser, float headDamage, float bodyDamage) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamagerCauser) override;
	virtual void ApplyExplosionDamage_Implementation(float BaseDamage,
		float MinimumDamage, const FVector& Origin, float DamageInnerRadius,
		float DamageOuterRadius, float DamageFallOf, AActor* DamageCauser) override;
private:
	//variables
	bool bInputComponentInitialised;
	UPROPERTY(EditAnywhere, Category = Bones)
		bool bCanPlayShieldSound = true;
	UPROPERTY(VisibleAnywhere, category = "Health & Sheild")
		float CurrentHealth = 100.f;
	UPROPERTY(VisibleAnywhere, category = "Health & Sheild")
		float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, category = "Health & Sheild")
		float CurrentShield = 100.f;
	UPROPERTY(VisibleAnywhere, category = "Health & Sheild")
		float MaxShield = 100.f;
		UPROPERTY(VisibleAnywhere, category = "Health & Sheild", BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		float MaxStamina = 100.f;
	UPROPERTY(VisibleAnywhere, category = "Health & Sheild",BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	float CurrentStamina = 100.f;
	UPROPERTY(EditAnywhere, category = "Health & Sheild",BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float DrainRate = 2.f;
	UPROPERTY(EditAnywhere, Category = Bones)
		FName HeadBoneName = "head";
	UPROPERTY(EditAnywhere, Category = Bones)
		FName NeckBoneName = "neck_01";
	UPROPERTY(EditAnywhere, Category = Speed)
		float SprintSpeed = 1200.f;
	UPROPERTY(EditAnywhere, Category = Speed)
		float WalkSpeed = 600.f;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		bool bIsSprinting;
	bool bIsTargeting;
	bool bWantsToRun;
	bool bWantsToRunToggled;
	bool bCanShoot;
	bool bCanJump = true;
	bool bCanAim = true;
	float TargetingSpeedModifier;
	float RunningSpeedModifier;
	bool bIsJumpPressed = false;
	float CurrentFOV;
	bool bIsFiring = false;
	UPROPERTY(VisibleAnywhere, Category = Camera)
		float DefaultFOV = 90.f;
	bool bCanInterpFOV;
	UPROPERTY(VisibleAnywhere, Category = Team)
		int32 MyTeamID = 0;
	ABaseWeapon* StartingWeapon;
	ABaseWeapon* SecondWeapon;
	ABaseWeapon* OverlappedWeapon;
	FVector BulletHitLocation=FVector::ZeroVector;

private:
	//Sound Anim related variables
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		class USoundCue* ShieldBreakSound;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
			USoundCue* AimSound;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
			USoundCue* JumpSound;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		USoundCue* JumpLandSound;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
			USoundCue* RunSound;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		TSubclassOf<class UCameraShakeBase> ShieldBreakCameraShake;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		TSubclassOf<class UCameraShakeBase> ExplosionCameraShake;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations", meta = (AllowPrivateAccess = true))
		TSubclassOf<class UCameraShakeBase> HitCameraShake;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		UAnimMontage* FireWeaponMontage;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		UAnimMontage* ReloadWeaponMontage;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		UAnimMontage* GrenadeThrowMontage;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		UAnimMontage* HealConsumeMontage;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		UAnimMontage* WeaponSwapMontage;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations", BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		USplineComponent* GrenadeSpline;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations", BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* GrenadeEndPoint;
	UPROPERTY(EditAnywhere, Category = Weapons, meta = (AlloprivateAccess = true))
		TSubclassOf<ABaseWeapon> PrimaryWeapon;
	UPROPERTY(EditAnywhere, Category = Weapons, meta = (AlloprivateAccess = true))
		TSubclassOf<ABaseWeapon> SecondaryWeapon;
public:
	//Getters and Setters
	UCombatComponent* GetCombat() const;
	UFUNCTION(BlueprintCallable)
		FORCEINLINE UCameraComponent* GetFollowCamera() const { return WOICamera; }
	FORCEINLINE bool GetIsTargeting() const { return bIsTargeting; }
	UFUNCTION(BlueprintCallable)
		bool IsRunning() const;
	void PlayAnimationMontage(bool bIsAiming);
	UFUNCTION(BlueprintCallable)
		FORCEINLINE USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	ABaseWeapon* GetCurrentWeapon();
	void PlayReloadMontage();
	void PlayGrenadeMontage();
	void PlayConsumeMonatge();
	void PlayWeaponSwapMontage();
	void PlayEmptyMagSound();
	void SetOverlappedWeapon(ABaseWeapon* OverlapWeapon);
	FORCEINLINE UStaticMeshComponent* GetGrenadeEndPoint() const { return GrenadeEndPoint; }
	FVector GetHitTarget() const;
	UFUNCTION(BlueprintCallable,BlueprintPure)
		FORCEINLINE float  GetCurrentHealth() const { return CurrentHealth; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE float  GetTotalHealth() const { return MaxHealth; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE float  GetCurrentShield() const { return CurrentShield; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE float  GetTotalShield() const { return MaxShield; }
	UFUNCTION(BlueprintCallable)
		void SetHealHealth(float NewHealth);
	UFUNCTION(BlueprintCallable)
	void SetShieldHeal(float NewShield);

	FORCEINLINE bool GetIsFiring() const { return bIsFiring; }
	bool IsWeaponEquipped();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABaseWeapon* GetPrimaryWeapon();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	ABaseWeapon* GetSecondaryWeapon();  
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE FVector GetHitLocation()const { return BulletHitLocation; }
       UFUNCTION(BlueprintImplementableEvent)
       void SpawnHitIndicators();

       UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetAmmoWidget(EAmmoType AmmoType, int32 AmountPickedUp);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void LaunchGrenade();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void SetWidgetDisplayText(FName Text);

	UPROPERTY(BlueprintReadOnly)
	bool bIsSniperScoping = false;
	UPROPERTY(EditAnywhere, Category = "Sounds & VFX  & Animations")
		USoundCue* EmptyMagSound;

};
