// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "StatusEffectComponent.generated.h"

class AStatusEffect;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEffectDelegate, FGameplayTag, GameplayTag, int32, EffectValue);


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

	UFUNCTION(BlueprintCallable)
	void InitializeEffects();

	//UFUNCTION(BlueprintCallable)
	//void SetEffectOnRemoveTimer(AStatusEffect* Effect);

	//UFUNCTION(BlueprintCallable)
	//void NewTurnStarted();

	//UPROPERTY()
	FEffectDelegate OnEffectFire;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	TArray<AStatusEffect*> Effects;		
};
