// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ProjectileWeapon/SniperRifle.h"
#include "Camera/CameraComponent.h"

ASniperRifle::ASniperRifle()
{
	WeaponType = EWeaponType::EWT_Sniper;
	AmmoTypeForWeapon = EAmmoType::EAT_HeavyAmmo;
	ScopeCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SniperScope"));
	ScopeCamera->SetupAttachment(GetRootComponent());
}