// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/GrenadeLauncherAmmo.h"

AGrenadeLauncherAmmo::AGrenadeLauncherAmmo()
{
	AmmoType = EAmmoType::EAT_GrenadeAmmo;
	minAmmoRange = 1;
	maxAmmoRange = 3;
}