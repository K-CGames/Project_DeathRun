// Fill out your copyright notice in the Description page of Project Settings.


#include "Healings/HealthKit.h"
#include "Interfaces/PickupInterface.h"
#include "Components/SphereComponent.h"
#include "Character/WOICharacter.h"

AHealthKit::AHealthKit()
{
	AmountToHeal = 20.f;
}

void AHealthKit::BeginPlay()
{
	Super::BeginPlay();
	if (HealSphere)
	{
		HealSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnHealSphereOverlap);
		HealSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnHealSphereEndOverlap);
	}
}


void AHealthKit::OnHealSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AWOICharacter* Character = Cast<AWOICharacter>(OtherActor);
	if (Character)
	{
		if (Character->GetCurrentHealth() < 75.f)
		{
			Character->SetHealHealth(AmountToHeal);
			//Character->IsPickedupHealing(true);
			Destroy();
		}
		else
		{
			HealItem->SetRenderCustomDepth(true);
			//HealItem->CustomDepthStencilValue = 1.0f;
			Character->SetWidgetDisplayText(FName("Health is More than 75"));
			UE_LOG(LogTemp, Warning, TEXT("Can't pickup health since more than 75"));
		}
	}
}

void AHealthKit::OnHealSphereEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWOICharacter* Character = Cast<AWOICharacter>(OtherActor);
	if (Character)
	{
		HealItem->SetRenderCustomDepth(false);
		HealItem->CustomDepthStencilValue = 0.f;
	}
}
