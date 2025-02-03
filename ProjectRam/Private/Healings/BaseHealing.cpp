// Fill out your copyright notice in the Description page of Project Settings.


#include "Healings/BaseHealing.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
// Sets default values
ABaseHealing::ABaseHealing()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	HealSphere = CreateDefaultSubobject<USphereComponent>(TEXT("HealingSphere"));
	HealItem = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HealItem"));
	SetRootComponent(HealSphere);
	HealItem->SetupAttachment(HealSphere);
	HealWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealWidget"));
	HealWidget->SetupAttachment(HealSphere);
	HealItem->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECR_Ignore);
	HealItem->CastShadow = false;
	HealItem->SetRenderCustomDepth(true);
	HealItem->CustomDepthStencilValue = 1.0f;
}

