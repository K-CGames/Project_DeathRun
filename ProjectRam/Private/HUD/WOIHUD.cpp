// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/WOIHUD.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/WOICharacter.h"
#include "Character/WOIPlayerController.h"
#include "Weapon/BaseWeapon.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Kismet/GameplayStatics.h"

AWOIHUD::AWOIHUD()
{
	CrosshairAimFactorVariable = 1.5f;
}

void AWOIHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawWeaponCrosshairs(GetWorld()->DeltaTimeSeconds);
}

void AWOIHUD::DrawCrosshair(UTexture2D* Texture, FVector2D ViewportSize, FVector2D Spread, FLinearColor CrosshairColor)
{
	const float TextureWidth = Texture->GetSizeX();
	const float TextureHeight = Texture->GetSizeY();
	const FVector2D TextureDrawPoint(
		ViewportSize.X - (TextureWidth / 2.f) + Spread.X,
		ViewportSize.Y - (TextureHeight / 2.f) + Spread.Y);
	//Inbuit function
	DrawTexture(Texture, TextureDrawPoint.X, TextureDrawPoint.Y,
		TextureWidth, TextureHeight, 0.f, 0.f, 1.f, 1.f, CrosshairColor);
}

float AWOIHUD::CalculateCrosshairSpread(float DeltaTime)
{
	FVector2D WalkSpeedRange(0.f, Pawn->GetCharacterMovement()->MaxWalkSpeed);
	FVector2D VelocityMultiplierRange(0.f, 2.f);
	FVector Velocity = Pawn->GetVelocity();
	Velocity.Z = 0.f;
	//Crosshair velocity Factor
	CrosshairVelocityFactor = FMath::GetMappedRangeValueClamped(WalkSpeedRange, VelocityMultiplierRange, Velocity.Size());


	if (Pawn->GetCharacterMovement()->IsFalling())
	{
		CrosshairAirFactor = FMath::FInterpTo(CrosshairAirFactor, 2.25f, DeltaTime, 2.25f);
	}
	else
	{
		CrosshairAirFactor = FMath::FInterpTo(CrosshairAirFactor, 0.f, DeltaTime, 20.f);
	}
	if (Pawn->GetIsFiring())
	{
		CrosshairShootingFactor = 0.75f;
	}
	if (Pawn->GetIsTargeting())
	{
		CrosshairAimFactor = FMath::FInterpTo(CrosshairAimFactor, CrosshairAimFactorVariable, DeltaTime, 20.f);
	}
	else
	{
		CrosshairAimFactor = FMath::FInterpTo(CrosshairAimFactor, 0.f, DeltaTime, 20.f);
	}
	CrosshairShootingFactor = FMath::FInterpTo(CrosshairShootingFactor, 0.f, DeltaTime, 40.f);
	CrosshairSpread = CrosshairMoreSpread + CrosshairVelocityFactor + CrosshairAirFactor + CrosshairShootingFactor - CrosshairAimFactor;
	return CrosshairSpread;
}

void AWOIHUD::DrawWeaponCrosshairs(float deltatime)
{
	auto  PCOwner = Cast<AController>(PlayerOwner);
	FVector2D ViewportSize;
	if (PCOwner)
	{
		Pawn = Cast<AWOICharacter>(PCOwner->GetPawn());
		if (Pawn && Pawn->IsWeaponEquipped() && Pawn->GetCurrentWeapon())
		{
			CalculateCrosshairSpread(deltatime);
			ABaseWeapon* Weapon = Cast<ABaseWeapon>(Pawn->GetCurrentWeapon());
			if (Weapon == NULL) return;

			GEngine->GameViewport->GetViewportSize(ViewportSize);
			const FVector2D ViewportCenter(ViewportSize.X / 2.f, ViewportSize.Y / 2.f);
			float SpreadScaled = CrosshairMaxSpread * CrosshairSpread;

			if (Weapon && !Pawn->IsRunning())
			{
				if (Weapon->CrosshairCenter)
				{
					FVector2D Spread(0.f, 0.f);
					DrawCrosshair(Weapon->CrosshairCenter, ViewportCenter, Spread, FLinearColor::White);
				}
				if (Weapon->CrosshairTop)
				{
					FVector2D Spread(0.f, -SpreadScaled);
					DrawCrosshair(Weapon->CrosshairTop, ViewportCenter, Spread, FLinearColor::White);
				}
				if (Weapon->CrosshairDown)
				{
					FVector2D Spread(0.f, SpreadScaled);
					DrawCrosshair(Weapon->CrosshairDown, ViewportCenter, Spread, FLinearColor::White);
				}
				if (Weapon->CrosshairRight)
				{
					FVector2D Spread(SpreadScaled, 0.f);
					DrawCrosshair(Weapon->CrosshairRight, ViewportCenter, Spread, FLinearColor::White);
				}
				if (Weapon->CrosshairLeft)
				{
					FVector2D Spread(-SpreadScaled, 0.f);
					DrawCrosshair(Weapon->CrosshairLeft, ViewportCenter, Spread, FLinearColor::White);
				}
			}
		}
	}
}
