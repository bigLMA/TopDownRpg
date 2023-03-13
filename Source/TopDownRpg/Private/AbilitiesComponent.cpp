// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitiesComponent.h"
#include "AbilityBase.h"

// Sets default values for this component's properties
UAbilitiesComponent::UAbilitiesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UAbilitiesComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Add to active abilities all abilities from book
void UAbilitiesComponent::InitializeAbilties()
{
	ActiveAbilities.SetNum(ActiveSlots);

	for (int32 Index = 0; Index < AbilityBook.Num(); ++Index)
	{
		if (AbilityBook.IsValidIndex(Index))
		{
			AddActiveAbility(Index);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("NO"))
		}
	}
}


//Adds new ability to ability book
void UAbilitiesComponent::AddToAbilityBook(TSubclassOf<AAbilityBase> AbilityToAddClass)
{
	auto NewIndex = AbilityBook.Add(AbilityToAddClass);

	if(NewIndex<ActiveSlots)
	{
		AddActiveAbility(NewIndex);
	}
	else if (NewIndex >= ActiveSlots && bShouldAddAbilitiesToFullSlots)
	{
		AddActiveAbility(NewIndex%ActiveSlots);
	}
}


// Adds active ability from ability book
void UAbilitiesComponent::AddActiveAbility(int32 BookIndex, int32 AbilitySlot)
{
	// if slot is -1 and index 

	// if slot is -1 and index less than active slots count
	if (AbilitySlot == -1 && BookIndex < ActiveSlots)
	{	
		// add spell from book with index to appropriate slot
		FActorSpawnParameters SpawnParams;
		auto NewAbility = GetWorld()->SpawnActor<AAbilityBase>(AbilityBook[BookIndex], SpawnParams);
		ActiveAbilities[BookIndex] = NewAbility;
	}
	else if (AbilitySlot>-1 && AbilitySlot<ActiveSlots)			// if slot is less than active slots count abd bigger than -1
	{
		// add spell to slot index
		FActorSpawnParameters SpawnParams;
		auto NewAbility = GetWorld()->SpawnActor<AAbilityBase>(AbilityBook[BookIndex], SpawnParams);
		ActiveAbilities[AbilitySlot] = NewAbility;
	}

	

		
}
