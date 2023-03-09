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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItem SlotItem;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 SlotQuantity;

	FSlot()
	{
		SlotItem = FItem();
		SlotQuantity = 0;
	}

	FSlot(FItem Item, int32 Quantity)
	{
		SlotItem = Item;
		SlotQuantity = Quantity;
	}
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UFUNCTION(BlueprintCallable)
	void AddToInventory(AInventoryItemBase* ItemToAdd);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleInventory(UInventoryComponent* Container = nullptr);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RefreshInventory();

	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory(int32 SlotIndex);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory name")
	FText InventoryName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory size")
	int32 InventorySize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TArray<FSlot> Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory widget")
	UUserWidget* InventoryWidget;

private:
	void CreateNewStack(AInventoryItemBase* Item);

	bool CheckOtherStacks(AInventoryItemBase* Item, int32& InventoryIndex) const;

	void AddToStack(int32 SlotIndex);
};
