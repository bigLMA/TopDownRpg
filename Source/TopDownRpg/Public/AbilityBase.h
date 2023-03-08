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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag StatToScale;

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

	UFUNCTION(BlueprintCallable)
	void PrepareAbility();

	UFUNCTION(BlueprintCallable)
	void ActivateAbility();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayAnimation();

	UFUNCTION(BlueprintCallable)
	void CastAbility();

	UFUNCTION(BlueprintCallable)
	void SetAbilityCaster(AAiCharacter* Target);

	UFUNCTION(BlueprintCallable)
	void AddAbilityTarget(AAiCharacter* Target);

	UFUNCTION(BlueprintCallable)
	void SetAbilityOnCooldown();

	UFUNCTION(BlueprintCallable)
	void DecreaseCooldown();

	UFUNCTION(BlueprintCallable)
	bool IsAbilityOnCooldown();

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentCooldown();

	UFUNCTION(BlueprintCallable)
	bool CalculateAbilityChance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info")
	FText AbilityName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info")
	FText AbilityDescription;

	// Determines way of ability cast behaviour
	// Use children tags of "AbilityFeatures" tag for this variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Ability feature")
	FGameplayTag AbilityFeature;

	// Determines base chance of ability applied successfully
	// 100 means ability success is guaranteed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|SuccessChance", meta =(ClampMin = 1, UIMin = 1, ClampMax = 100, UIMax = 100))
	int32 BaseChance = 100;

	// Determins which skill is going to influence succsess chance
	// Use chid children tags of "Stats.Skills" tag for this variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Success chance", meta = (EditCondition = "BaseChance<100"))
	FGameplayTag CasterSkill;

	// Determins which skill is going to influence succsess chance
	// Use chid children tags of "Stats.AbilityDefecne" tag for this variable
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Success chance", meta = (EditCondition = "BaseChance<100"))
	FGameplayTag TargetAbilityDefence;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Cooldown")
	int32 AbilityCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Cost")
	int32 EnergyCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|Animation")
	UAnimMontage* AbilityMontage;

	// Use only if ability feature is has spawn actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|SpawnActor")
	bool bHasSpawnActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability info|SpawnActor", meta = (EditCondition = "bHasSpawnActor"))
	TSubclassOf<AActor> SpawnActor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Thumbnail")
	UTexture2D* AbilityThumbnail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability Composition")
	TArray<FAbilityComposition> AbilityComposition;

	UPROPERTY(BlueprintReadOnly, Category = "Caster")
	AAiCharacter* AbilityCaster;

	UPROPERTY(BlueprintReadOnly, Category = "Target")
	TArray<AAiCharacter*> AbilityTargets;

private:
	int32 CurrentCooldown = 0;

	int32 CurrentCost;

	// Variable to count ability cooldown while not in fight
	int32 SecondsPerTurn = 4;

	FTimerHandle Timer;
};
