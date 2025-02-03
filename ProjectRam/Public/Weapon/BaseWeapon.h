// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponTypes.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UAnimationAssest;
class USoundCue;
//class UObjectPoolComponent;

UCLASS()
class PROJECTRAM_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ABaseWeapon();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Fire(const FVector& HitTarget);	    //Overrides in Child
	void SpendAmmo();
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		EAmmoType AmmoTypeForWeapon;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		EWeaponType WeaponType;
	//UFUNCTION()
	//	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
	//		AActor* OtherActor,
	//		UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex,
	//		bool bFromSweep,
	//		const FHitResult& Hit);
	//UFUNCTION()
	//	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComp,
	//		AActor* OtherActor,
	//		UPrimitiveComponent* OtherComp,
	//		int32 OtherBodyIndex);
	void DetermineWeaponState();
	void WeaponIdleState();
	void WeaponInInventory();
	void WeaponDrop();
	//UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	//	UObjectPoolComponent* PoolComponent;

	UPROPERTY(EditAnywhere, Category = Weapon)
		USoundCue* ImpactSound;

private:

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* GunMesh;
/*	UPROPERTY(EditAnywhere)
		USphereComponent* GunSphere;*/		  //Remove this @DEPRECATED
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = Weapon)
		UAnimationAsset* FireAnimation;
	UPROPERTY(EditAnywhere, Category = Weapon)
		USoundCue* PickupSound; //Sound played when we pickup weapon...Different for diff weapon
	UPROPERTY(EditAnywhere, Category = Weapon)
		UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = Weapon)
		USoundCue* DropSound;
	UPROPERTY(EditAnywhere, Category = Weapon)
		USoundCue* FireSound;
	UPROPERTY(EditAnywhere, Category = Weapon)
		UAnimationAsset* ReloadAnimation;
	UPROPERTY(VisibleAnywhere, Category = Weapon)
		EWeaponState WeaponState;
	FTimerHandle DestroyDroppedWeaponTimer;
	void DestroyDroppedWeapon();
private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = Ammo)
		int32 Ammo;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true), Category = Ammo)
		int32 MagCapacity;
	UPROPERTY(EditAnywhere, Category = Ammo)
		bool bIsAutomatic = false;
	UPROPERTY(EditAnywhere, Category = Ammo)
		float TimeBetweenShots = 0.15f;
	UPROPERTY(EditAnywhere, Category = CameraShake, meta = (AllowPrivateAccess = true))
		TSubclassOf<class UCameraShakeBase> CameraShake;
	UPROPERTY(VisibleAnywhere, Category = Inventory);
	int32 SlotIndex;
public:
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		int32 StartingSmallAmmo = 15;
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		int32 StartingMediumAmmo = 30;
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		int32 StartingHeavyAmmo = 5;
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		int32 StartingGrenadeAmmo = 2;
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		int32 MaxSmallAmmo = 150;
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		int32 MaxMediumAmmo = 175;
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		int32 MaxHeavyAmmo = 30;
	UPROPERTY(VisibleAnywhere, Category = Ammo)
		int32 MaxGrenadeAmmo = 10;
	UPROPERTY(EditAnywhere, Category = Aiming)
		float AimFOV = 72.5f;
	UPROPERTY(EditAnywhere, Category = Weapon)
		FName SocketName;
public:

	//HUD variables
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	class UTexture2D* CrosshairCenter;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	class UTexture2D* CrosshairTop;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	class UTexture2D* CrosshairDown;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	class UTexture2D* CrosshairLeft;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	class UTexture2D* CrosshairRight;

public:
	FORCEINLINE FName GetSocketName() { return SocketName; }
	FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const { return GunMesh; }
	void FireWeapon(const FVector& HitTarget);
	void SetWeaponState(EWeaponState NewState);
	bool IsMagFull();
	bool IsMagEmpty();
	bool IsAutomaticWeapon() const;
	float GetTimeBetweenShots();
	FORCEINLINE EAmmoType GetWeaponAmmoType() const { return AmmoTypeForWeapon; }
	void WeaponDetails();
	UFUNCTION(BlueprintCallable)
		EWeaponType GetWeaponType();
	FORCEINLINE EWeaponState GetWeaponState() { return WeaponState; }
	int32 GetMagCapacity();
	UFUNCTION(BlueprintCallable, BlueprintPure)
		int32 GetAmmo() const;
	FORCEINLINE EAmmoType GetAmmoTypeForWeapon() const { return AmmoTypeForWeapon; }
	void AddAmmo(int32 AmmoToAdd);
	void FireAIWeapon(const FVector& HitTarget);
	void HandleReloading();
	void SetSlotIndex(int32 newSlotIndex) {
		SlotIndex = newSlotIndex;
	}
	FORCEINLINE int32 GetSlotIndex() const { return SlotIndex; }

	UFUNCTION(BlueprintImplementableEvent)
		void SpawnMuzzleFlash();
		void GetScreenCenterLocation(FVector& CrosshairWorldLocation);
};
