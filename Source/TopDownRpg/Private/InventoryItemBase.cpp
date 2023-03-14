// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AInventoryItemBase::AInventoryItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ActorRootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(ActorRootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static mesh");
	StaticMesh->SetupAttachment(ActorRootComponent);

	Collision = CreateDefaultSubobject< UBoxComponent>("Collision");
	Collision->SetupAttachment(ActorRootComponent);
}

// Called when the game starts or when spawned
void AInventoryItemBase::BeginPlay()
{
	Super::BeginPlay();
}


// Calls use item
// Return should destroy item on use
bool AInventoryItemBase::UseItem_Implementation()
{
	UseItemInternal();

	return ItemInfo.bShouldDestroyItemOnUsed;
}


// Implementation of use item
void AInventoryItemBase::UseItemInternal()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is used"), *GetName())
	Destroy();
}

// Gets item info
FItem& AInventoryItemBase::GetItemInfo()
{
	return ItemInfo;
}
