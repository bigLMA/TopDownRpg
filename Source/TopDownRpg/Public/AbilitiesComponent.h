// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AbilitiesComponent.generated.h"

class AAbilityBase;

/*
* Component that handles cast of character abilities
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOPDOWNRPG_API UAbilitiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilitiesComponent();

	// Add to active abilities all abilities from book
	UFUNCTION(BlueprintCallable)
	void InitializeAbilties();

	//Adds new ability to ability book
	UFUNCTION(BlueprintCallable)
	void AddToAbilityBook(TSubclassOf<AAbilityBase> AbilityToAddClass);

	// Adds active ability from ability book
	UFUNCTION(BlueprintCallable)
	void AddActiveAbility(int32 BookIndex, int32 AbilitySlot = -1);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// All abilities known to character
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability book")
	TArray<TSubclassOf<AAbilityBase>> AbilityBook;

	// All abilities character currently can cast
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Active abilities")
	TArray<AAbilityBase*>ActiveAbilities;

	// Defines how much active slots to add
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Active abilities slots")
	int32 ActiveSlots = 10;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Active abilities|Add new active abilities")
	bool bShouldAddAbilitiesToFullSlots = false;
};
