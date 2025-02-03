// Fill out your copyright notice in the Description page of Project Settings.


#include "Healings/MedKit.h"
#include "Components/SphereComponent.h"
#include "Interfaces/PickupInterface.h"
#include "Character/WOICharacter.h"

AMedKit::AMedKit()
{
	AmountToHeal = 50.f;
}

void AMedKit::BeginPlay()
{
	if (HealSphere)
	{
		HealSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnHealSphereOverlap);
		HealSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnHealSphereEndOverlap);
	}
}

void AMedKit::OnHealSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AWOICharacter* Character = Cast<AWOICharacter>(OtherActor);
	if (Character)
	{
			if (Character->GetCurrentHealth() < 100.f)
			{
				Character->SetHealHealth(AmountToHeal);
				Destroy();
			}
			else
			{
				HealItem->SetRenderCustomDepth(true);
				//HealItem->CustomDepthStencilValue = 1.0f;
				Character->SetWidgetDisplayText(FName("Health is Full!!"));
			}

	}
}

void AMedKit::OnHealSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWOICharacter* Character = Cast<AWOICharacter>(OtherActor);
	if (Character)
	{
		HealItem->SetRenderCustomDepth(false);
		HealItem->CustomDepthStencilValue = 0.f;
	}
}
