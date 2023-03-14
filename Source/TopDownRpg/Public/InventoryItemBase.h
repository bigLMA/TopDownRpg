// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "InventoryItemBase.generated.h"

class UBoxComponent;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AInventoryItemBase> Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bShouldDestroyItemOnUsed;

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
		bShouldDestroyItemOnUsed = true;
	}
};

UCLASS()
class TOPDOWNRPG_API AInventoryItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryItemBase();

	// Calls use item
	// Return should destroy item on use
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool UseItem();

	// Gets item info
	FItem& GetItemInfo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Implementation of use item
	virtual void UseItemInternal();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item info")
	FItem ItemInfo;

	UPROPERTY(EditDefaultsOnly,Category = "Root")
	USceneComponent* ActorRootComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Static mesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	UBoxComponent* Collision;
};
