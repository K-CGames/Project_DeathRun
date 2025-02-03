// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo/BaseAmmo.h"
#include "Components/SphereComponent.h"
#include "Interfaces/PickupInterface.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Character/WOICharacter.h"
#include "Component/CombatComponent.h"

// Sets default values
ABaseAmmo::ABaseAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ItemSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ItemSphere"));
	SetRootComponent(ItemSphere);
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	AmmoType = EAmmoType::EAT_SmallAmmo;
	ItemMesh->SetRenderCustomDepth(true);
	ItemMesh->bRenderCustomDepth = true;
	ItemMesh->CustomDepthStencilValue = 1.0f;
	ItemMesh->CastShadow = true;
	minAmmoRange = 5;
	maxAmmoRange = 10;

}
// Called when the game starts or when spawned
void ABaseAmmo::BeginPlay()
{
	Super::BeginPlay();
	if (ItemSphere)
	{
		ItemSphere->OnComponentBeginOverlap.AddDynamic(this, &ABaseAmmo::OnSphereOverlap);
	}

}

// Called every frame
void ABaseAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseAmmo::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AWOICharacter* Character = Cast<AWOICharacter>(OtherActor);
	if (Character)
	{
		UCombatComponent* Combat = Character->GetCombat();
		if (Combat)
		{
			Combat->PickupAmmo(AmmoType, FMath::RandRange(minAmmoRange, maxAmmoRange));
			if (PickupSound)
			{
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupSound, GetActorLocation());
			}
			Destroy();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Doesn't implement interface %s"), *OtherActor->GetName());
		return;
	}
}

