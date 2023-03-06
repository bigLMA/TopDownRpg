// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "StatusEffect.generated.h"

UENUM(BlueprintType)
enum class EEffectDuration : uint8
{
	Instant, Constant, Duration
};

UENUM(BlueprintType)
enum class EEffectFiring : uint8
{
	Once, PerTurn
};

USTRUCT(BlueprintType)
struct FEffectComposition
{
	GENERATED_USTRUCT_BODY()

	// Tag regulates which stat or state container affects
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag EffectTag;

	// If affects stat, regulate how much add or substract from stat,
	// If affect state, positive number adds state, while negative purges
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 EffectValue;
};

UCLASS()
class TOPDOWNRPG_API AStatusEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatusEffect();

	UFUNCTION(BlueprintCallable)
	TArray<FEffectComposition> GetEffectComposition();

	UFUNCTION(BlueprintCallable)
	EEffectDuration GetDuration();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info")
	FText EffectName;

	// Effect duration, regulates how is effect added and removed within status effect component.
	// Can be instant, constant or durational. Constant and durational effects revert their effects applied.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info|Effect Duration")
	EEffectDuration	EffectDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Thumbnail", meta = (EditCondition = "bHasThumbnail"))
	UTexture2D* EffectThumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Containers")
	TArray<FEffectComposition> EffectComposition;

	// If effect has certain duration (Constant or Duration), this variable regulates effect firing logic
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info|EffectFiring", meta = (EditCondition = "EffectDuration!=EEffectDuration::Instant"))
	EEffectFiring EffectFiring;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Effect Thumbnail")
	bool bHasThumbnail;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Visuals")
	//bool bHasVisuals;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Visuals")
	//UParticleSystem* EffectVisual;
	// TODO Effects effects
	
private:
	int32 CurrentDuration;
};
