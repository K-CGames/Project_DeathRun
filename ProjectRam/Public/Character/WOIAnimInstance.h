// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WOIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRAM_API UWOIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:

	virtual void NativeInitializeAnimation() override;
	/**
	* This function behaves as Tick in AnimInstance Class;
	*/
	virtual void NativeUpdateAnimation(float DeltaTime) override;
private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		class AWOICharacter* WOICharacter;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		class ABaseWeapon* CurrentWeapon;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		bool bIsInAir;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		float Speed;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		bool bIsSprinting;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		bool bIsPistol;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		bool bWeaponEquipped;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		bool bIsAiming;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		bool bIsWalking;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		FTransform LeftHandTransform;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		FRotator RightHandRotation;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true), Category = Weapon)
		bool bIsReloading;
};
