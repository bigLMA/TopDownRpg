// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemBase.h"
#include "InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FSlot
{
	GENERATED_USTRUCT_BODY()

	// Item information
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItem SlotItem;
	
	//Quantity
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 SlotQuantity;

	// Default constructor with no values
	FSlot()
	{
		SlotItem = FItem();
		SlotQuantity = 0;
	}

	// Constructor that sets values
	FSlot(FItem Item, int32 Quantity)
	{
		SlotItem = Item;
		SlotQuantity = Quantity;
	}
};

UCLASS(Blueprintable, ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Adds item to inventory
	UFUNCTION(BlueprintCallable)
	void AddToInventory(AInventoryItemBase* ItemToAdd);

	// Turns off/on inventory widget, allows to turn inventory container
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleInventory(UInventoryComponent* Container = nullptr);

	// Sets inventory variables according to class delault values
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshInventory();

	// Remomes slot from inventory
	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory(int32 SlotIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Inventory name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory name")
	FText InventoryName;

	// How much slots to create
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory size")
	int32 InventorySize;

	// Inventory
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<FSlot> Inventory;

	// Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory widget")
	UUserWidget* InventoryWidget;

private:
	// Creates new stack
	void CreateNewStack(AInventoryItemBase* Item);

	// Looks for aviable stacks 
	bool CheckOtherStacks(AInventoryItemBase* Item, int32& InventoryIndex) const;

	// Adds item to existing stack
	void AddToStack(int32 SlotIndex);

	// Check if there is need to add new inventory slots
	void TryToExpandInventory();

	// Check if there is need to cut inventory slots
	void TryToReduceInventory();

	int32 SlotDifferenceToChangeSize = 6;
};
