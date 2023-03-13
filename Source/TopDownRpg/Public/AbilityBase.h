// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "AbilityBase.generated.h"

class AStatusEffect;
class AAiCharacter;

USTRUCT(BlueprintType)
struct FSkalingValues
{
	GENERATED_USTRUCT_BODY()

	// Which stat to take from stats component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag StatToScale;

	// What percent of stat is to add to effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ScalingPercent;
};

USTRUCT(BlueprintType)
struct FAbilityComposition
{
	GENERATED_USTRUCT_BODY()

	// Which class of effect ability should spawn
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AStatusEffect> EffectToSpawn;

	// Set of stats which modified with scaling percent, which added to spawned effect value
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FSkalingValues> SkalingValues;
};

UCLASS()
class TOPDOWNRPG_API AAbilityBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbilityBase();

	// Prepares ability to cast, allowing player to choose cast target, area etc
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PrepareAbility();

	// Starts ability to behave, starts cooldown, animation etc
	UFUNCTION(BlueprintCallable)
	void ActivateAbility();

	// Play ability animation
	UFUNCTION(BlueprintCallable)
	void PlayAnimation();

	// Implementable event for cast on blueprints
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CastAbility();

	// Set character who casts ability
	UFUNCTION(BlueprintCallable)
	void SetAbilityCaster(AAiCharacter* Target);

	// Add ability target (sets if target is single)
	UFUNCTION(BlueprintCallable)
	void AddAbilityTarget(AActor* Target);

	// Make ability unable to cast during cooldown
	UFUNCTION(BlueprintCallable)
	void SetAbilityOnCooldown();

	// Decrease cooldown by one
	UFUNCTION(BlueprintCallable)
	void DecreaseCooldown();

	// Returns if ability is on cooldown
	UFUNCTION(BlueprintCallable)
	bool IsAbilityOnCooldown();

	// Returns current cooldown value
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentCooldown();

	// Calculates if ability reaches target actors
	UFUNCTION(BlueprintCallable)
	bool CalculateAbilityChance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Ability name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info")
	FText AbilityName;

	// Ability description
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info")
	FText AbilityDescription;

	//// Determines way of ability cast behaviour
	//// Use children tags of "AbilityFeatures" tag for this variable
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Ability feature")
	//FGameplayTag AbilityFeature;

	// Determines base chance of ability applied successfully
	// 100 means ability success is guaranteed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|SuccessChance", meta =(ClampMin = 1, UIMin = 1, ClampMax = 100, UIMax = 100))
	int32 BaseChance = 100;

	// Determins which skill is going to influence succsess chance
	// Use chid children tags of "Stats.Skills" tag for this variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Success chance", meta = (EditCondition = "BaseChance<100"))
	FGameplayTag CasterSkill;

	// Determins which skill is going to influence succsess chance
	// Use chid children tags of "Stats.AbilityDefence" tag for this variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Success chance", meta = (EditCondition = "BaseChance<100"))
	FGameplayTag TargetAbilityDefence;

	// How many turns(or ticks) takes to refresh ability
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Cooldown")
	int32 AbilityCooldown;

	// How much energy to take from ability target
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Cost")
	int32 EnergyCost;

	// Anim montage to play
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Animation")
	UAnimMontage* AbilityMontage;

	// Use only if ability feature is has spawn actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|SpawnActor")
	bool bHasSpawnActor;

	// Use only if ability feature is has spawn actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|SpawnActor", meta = (EditCondition = "bHasSpawnActor"))
	TSubclassOf<AActor> SpawnActor;

	// Ability picture
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Thumbnail")
	UTexture2D* AbilityThumbnail;

	// Set of diiferent effects (or one effect) that should be applied on target
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Composition")
	TArray<FAbilityComposition> AbilityComposition;

	// Applies ability effects on target
	virtual void CastAbilityInternal();

	// Prepares ability to cast
	virtual void PrepareAbilityInternal();

private:
	int32 CurrentCooldown = 0;

	int32 CurrentCost;

	// Variable to count ability cooldown while not in fight
	int32 SecondsPerTurn = 4;

	FTimerHandle Timer;

	AAiCharacter* AbilityCaster;

	TArray<AActor*> AbilityTargets;




};
