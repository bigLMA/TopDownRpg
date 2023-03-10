// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "InventoryItemBase.generated.h"

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText  ItemName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* ItemImage;

	// Use children tags of "ItemType"
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ItemType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsStackble;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bIsStackble"))
	int32 MaxStackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Price;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Weight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AInventoryItemBase> Class;

	// Default constructor
	FItem()
	{
		ItemName = FText();
		ItemDescription = FText();
		ItemImage = nullptr;
		ItemType = FGameplayTag();
		bIsStackble = false;
		MaxStackSize = 0;
		Price = 0;
		Weight = 0;
		//Class = TSubclassOf<AInventoryItemBase>;
	}
};

UCLASS()
class TOPDOWNRPG_API AInventoryItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItemBase();

	// Use item in a way function overridden by child classes
	UFUNCTION(BlueprintCallable)
	virtual void UseItem();

	// Gets item info
	FItem& GetItemInfo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item info")
	FItem ItemInfo;

};
