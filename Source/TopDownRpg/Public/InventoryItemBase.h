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
};

UCLASS()
class TOPDOWNRPG_API AInventoryItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItemBase();

	virtual void UseItem();

	FItem& GetItemInfo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item info")
	FItem ItemInfo;

};
