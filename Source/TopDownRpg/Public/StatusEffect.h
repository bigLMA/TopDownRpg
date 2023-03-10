// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "StatusEffect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEffectFiring, AStatusEffect*, Self)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinishEffect, AStatusEffect*, Self)

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

	// This value affects onle stats, regulate how much add or substract from stat
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 EffectValue;
};

UCLASS()
class TOPDOWNRPG_API AStatusEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStatusEffect();

	// Gets all values to change in effect
	UFUNCTION(BlueprintCallable)
	TArray<FEffectComposition> GetEffectComposition() const;

	// Gets effect duration
	UFUNCTION(BlueprintCallable)
	EEffectDuration GetDuration() const;

	// Gets effect firing
	UFUNCTION()
	EEffectFiring GetEffectFiring() const;

	// Gets current effect duration remaining
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentDuration() const;

	// Start timer (if realtime) to to decrease effect duration
	UFUNCTION(BlueprintCallable)
	void SetDurationTimer();

	// Decrease  duration value
	UFUNCTION(BlueprintCallable)
	void DecreaseDuration();

	// Sets effect duration
	UFUNCTION(BlueprintCallable)
	void RefreshDuration();

	// Returns if effect stacks
	UFUNCTION(BlueprintCallable)
	bool IsStackable();

	// Delegator to fire effect
	UPROPERTY()
	FEffectFiring OnFireEffect;

	// Delegator to finish effect
	UPROPERTY()
	FOnFinishEffect OnFinishEffect;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info")
	FText EffectName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info")
	FText EffectDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info|Effect Duration", meta = (EditCondition = "EffectDuration==EEffectDuration::Duration"))
	int32 BaseDuration;

	// Effect duration, regulates how is effect added and removed within status effect component.
	// Can be instant, constant or durational. Constant and durational fired once effects revert their effects applied.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info|Effect Duration")
	EEffectDuration	EffectDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info|Stackable")
	bool bIsStackable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Thumbnail", meta = (EditCondition = "bHasThumbnail"))
	UTexture2D* EffectThumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Composition")
	TArray<FEffectComposition> EffectComposition;

	// If effect has certain duration (Constant or Duration), this variable regulates effect firing logic
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Info|EffectFiring", meta = (EditCondition = "EffectDuration==EEffectDuration::Duration"))
	EEffectFiring EffectFiring;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,  Category = "Effect Thumbnail")
	bool bHasThumbnail;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Visuals")
	//bool bHasVisuals;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect Visuals")
	//UParticleSystem* EffectVisual;
	// TODO Effects effects and sound 
	
private:
	// Variable to count effect duration while not in fight
	int32 SecondsPerTurn = 4;

	FTimerHandle Timer;

	int32 CurrentDuration;
};