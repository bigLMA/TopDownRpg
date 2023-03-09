// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UInventoryComponent::AddToInventory(AInventoryItemBase* ItemToAdd)
{
	// Check if item is stackable
	if (!ItemToAdd->GetItemInfo().bIsStackble)
	{
		// Otherwise create new stack
		CreateNewStack(ItemToAdd);
	}
	else
	{
		int32 Index = 0;

		// Check for other stack with same class for place in stack
		if (CheckOtherStacks(ItemToAdd, Index))
		{
			// If there are add to first no full stack
			AddToStack(Index);
		}
		else
		{
			// Otherwise create new stack
			CreateNewStack(ItemToAdd);
		}
	}

	ItemToAdd->Destroy();
}



void UInventoryComponent::CreateNewStack(AInventoryItemBase* Item)
{
	Inventory.Add(FSlot(Item->GetItemInfo(), 1));
}



bool UInventoryComponent::CheckOtherStacks(AInventoryItemBase* Item, int32 & InventoryIndex) const
{
	auto ClassToFind = Item->GetItemInfo().Class;

	for (int32 Index = 0; Index<Inventory.Num(); ++Index)
	{
		if (Inventory[Index].SlotItem.Class == ClassToFind && Inventory[Index].SlotItem.MaxStackSize>Inventory[Index].SlotQuantity)
		{
			InventoryIndex = Index;

			return true;
		}
	}

	return false;
}



void UInventoryComponent::AddToStack(int32 SlotIndex)
{
	Inventory[SlotIndex].SlotQuantity += 1;
}
