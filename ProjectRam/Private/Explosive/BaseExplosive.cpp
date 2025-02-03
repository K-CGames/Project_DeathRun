// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive/BaseExplosive.h"

// Sets default values
ABaseExplosive::ABaseExplosive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ExplosiveMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Explosive"));
	SetRootComponent(ExplosiveMesh);

}

// Called when the game starts or when spawned
void ABaseExplosive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseExplosive::BulletHit_Implementation(FHitResult HitResult)
{
	UE_LOG(LogTemp, Error, TEXT("the barrel got hit"));
}

