// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "StatusEffectComponent.generated.h"

class AStatusEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEffectDelegate, FGameplayTag, GameplayTag, int32, EffectValue)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFinishEffectDelegate, FGameplayTag, GameplayTag, int32, EffectValue)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UStatusEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusEffectComponent();

	UFUNCTION(BlueprintCallable)
	void AddEffect(AStatusEffect* EffectToAdd);

	UFUNCTION(BlueprintCallable)
	void RemoveEffect(AStatusEffect* EffectToRemove);

	UFUNCTION(BlueprintCallable)
	void FireEffect(AStatusEffect* EffectToFire);

	// Function called when effect is removed from component, in order to revert effect changes
	UFUNCTION(BlueprintCallable)
	void FireFinishEffect(AStatusEffect* EffectToFire);

	UFUNCTION(BlueprintCallable)
	void InitializeEffects();

	UFUNCTION(BlueprintCallable)
	void LowerEffectDuration(AStatusEffect* Effect);

	// Returns true if effect is stackable or if no effects with similar class found
	UFUNCTION(BlueprintCallable)
	bool EnsureEffectStackable(AStatusEffect* EffectToEnsure, int32& EffectIndex);

	//UFUNCTION(BlueprintCallable)
	//void SetEffectOnRemoveTimer(AStatusEffect* Effect);

	//UFUNCTION(BlueprintCallable)
	//void NewTurnStarted();

	UPROPERTY()
	FEffectDelegate OnEffectFire;

	UPROPERTY()
	FFinishEffectDelegate FinishEffect;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TArray<AStatusEffect*> Effects;

private:
};
