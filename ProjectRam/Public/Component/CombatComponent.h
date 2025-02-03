// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponTypes.h"
#include "CombatComponent.generated.h"

class ABaseWeapon;
class AWOICharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTRAM_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	// Sets default values for this component's properties
	UCombatComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	friend class AWOICharacter;
	//void TraceUnderBarrel(FHitResult& HitResult);


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// Variables

	class AWOICharacter* WOICharacter;
	//class AWOIPlayerController* Controller;
	ABaseWeapon* EquippedWeapon;
	ABaseWeapon* SecondaryWeapon;
	FVector HitTarget;
	bool bIsADS = false;
	bool bFireButtonPressed = false;
	bool bCanFire = true;
	bool bAiming = false;
	bool bIsReloading = false;
	class AWOIPlayerController* Controller;
	UPROPERTY(EditAnywhere, Category = Trace)
		float ItemTraceLength = 8000.f; //Trace length for Items. (Its 8mts)
	EWeaponState StateofWeapon;
	ECombatState CombatState;
	EAmmoType AmmoType;
	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_CarriedAmmo)
		int32 CarriedAmmo = 30; //Total pickedup ammo		   //Remove this
	UFUNCTION()
		void OnRep_CarriedAmmo();
	UPROPERTY(VisibleAnywhere)
		TMap<EAmmoType, int32> CarriedAmmoMap;
	UPROPERTY(VisibleAnywhere, Category = HandGrenade)
		int32 maxAllowedGrenades = 5;
	int32 Grenades = 5;
	UPROPERTY(EditAnywhere, Category = Path)
		float XValue = 10.f;
	UPROPERTY(EditAnywhere, Category = Path)
		float YValue = 10.f;
	UPROPERTY(EditAnywhere, Category = Path)
		float ZValue = 10.f;
	UPROPERTY(EditAnywhere, Category = Path)
		float LaunchVelocityFactor = 750.f;
	UPROPERTY(EditAnywhere, Category = Path)
		float MaxSimTime = 1.f;
	UPROPERTY(EditAnywhere, Category = Path)
		float MaxSimFreq = 20.f;
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		TArray<ABaseWeapon*> Inventory;
	const int32 INVENTORY_SIZE = 2;
	ABaseWeapon* TracedWeapon;
	ABaseWeapon* OldEquippedWeapon;
	ABaseWeapon* NewWeapon;

private:

	void TraceUnderCrosshairs(FHitResult& HitResult);
	void TraceForWeapon();
	void EquipWeapon(ABaseWeapon* WeaponToEquip, AActor* NewOwner, APawn* NewInstigator);
	void SwapWeapon(ABaseWeapon* WeaponToSwap);
	void DropEquippedWeapon();
	void ReloadEmptyWeapon();
	void SwitchToADSCamera(bool bIsAiming);
	void SwitchToScopeCamera(bool bIsScopeAiming);
	void FireButtonPressed(bool IsPressed);
	void Fire();
	void StopFire();
	bool CanFire();
	void AttachActorToRightHand(ABaseWeapon* WeaponToAttach);
	void AttachActorToBackpack(AActor* ActorToAttach);
	void SwapInventoryWeapons(int32 CurrentItemIndex, int32 NewItemIndex, AActor* NewOwner, APawn* NewInstigator);
	UPROPERTY(EditAnywhere, Category = Combat)
		TSubclassOf<class ABaseGrenade> GrenadeClass;
	/**
	* Automatic fire
	*/
	FTimerHandle FireTimer;
	void StartFireTimer();
	void FireTimerFinished();
	void ReloadWeapon();
	void InitializeCarriedAmmo();
	bool ShouldSwapWeapons();
	void ThrowGrenade();
	void SetGrenadeVisibility(bool bShow);
	UFUNCTION(BlueprintCallable)
		void ThrowGrenadeFinished();
	UFUNCTION(BlueprintCallable)
	void ConsumingFinished();
	bool bCanThrowGrenade = true;
protected:

	void UpdateCarriedAmmo();
	void UpdateAmmoValues();
	int32 AmountToReload();
	
public:

	UFUNCTION(BlueprintCallable)
		void FinishReloading();
	UFUNCTION(BlueprintCallable)
		void PickupAmmo(EAmmoType AmmoPickupType, int32 AmmoAmount);

	UFUNCTION(BlueprintCallable,BlueprintPure)
		FORCEINLINE int32 GetGrenades() const { return Grenades; }

	UFUNCTION(BlueprintCallable,BlueprintPure)
		FORCEINLINE ABaseWeapon* GetEquippedWeapon() const { return EquippedWeapon; }
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE int32 GetCarriedAmmo() const { return CarriedAmmo; }
	
	UFUNCTION(BlueprintCallable,BlueprintPure)
	int32 GetTotalMediumAmmo();
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetTotalGrenadeAmmo();
	UFUNCTION(BlueprintCallable)
	void SetCombatState(ECombatState NewCombatState);
	UFUNCTION(BlueprintCallable)
	void WeaponSwapFinished();
};
