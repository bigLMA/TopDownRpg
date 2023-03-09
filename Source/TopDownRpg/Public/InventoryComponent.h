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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FItem SlotItem;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 SlotQuantity;

	FSlot(){}

	FSlot(FItem Item, int32 Quantity)
	{
		SlotItem = Item;
		SlotQuantity = Quantity;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintType)
	void AddToInventory(AInventoryItemBase* ItemToAdd);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TArray<FSlot> Inventory;

private:
	void CreateNewStack(AInventoryItemBase* Item);

	bool CheckOtherStacks(AInventoryItemBase* Item, int32& InventoryIndex) const;

	void AddToStack(int32 SlotIndex);
};
