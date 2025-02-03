// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WOIHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRAM_API AWOIHUD : public AHUD
{
	GENERATED_BODY()
public:
	AWOIHUD();
	virtual void DrawHUD() override;

private:
	void DrawCrosshair(UTexture2D* Texture, FVector2D ViewportSize, FVector2D Spread, FLinearColor CrosshairColor);
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float CrosshairMaxSpread = 16.f;

	float CalculateCrosshairSpread(float DeltaTime);

	void DrawWeaponCrosshairs(float deltatime);

private:
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float CrosshairVelocityFactor;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float CrosshairAirFactor;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float CrosshairAimFactor;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float CrosshairShootingFactor;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float CrosshairSpread;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float CrosshairAimFactorVariable = 1.5f;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float XOffset = 0.f;
	UPROPERTY(EditAnywhere, Category = Crosshairs)
	float YOffset = 0.f;
	UPROPERTY(EditAnywhere, Category = CrosshairSpread)
	float CrosshairMoreSpread = 1.5f;
	class AWOICharacter* Pawn;
};
