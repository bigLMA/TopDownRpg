// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemBase.h"

// Sets default values
AInventoryItemBase::AInventoryItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AInventoryItemBase::BeginPlay()
{
	Super::BeginPlay();
}


void AInventoryItemBase::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("%s is used"), *GetName())
}

FItem& AInventoryItemBase::GetItemInfo()
{
	return ItemInfo;
}
