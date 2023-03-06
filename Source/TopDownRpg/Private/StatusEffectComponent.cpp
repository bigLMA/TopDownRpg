// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"
#include "StatusEffect.h"

// Sets default values for this component's properties
UStatusEffectComponent::UStatusEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UStatusEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeEffects();
}


void UStatusEffectComponent::InitializeEffects()
{
	//for (auto Effect : Effects)
	//{
	//	FireEffect(Effect);
	//}
	bool bIsInstant = false;
	int32 Length = Effects.Num();

	for (int32 I = 0; I < Length; ++I)
	{
		if (bIsInstant)
		{
			--I;
		}

		if (!Effects.IsValidIndex(I))
		{
			break;
		}

		bIsInstant = Effects[I]->GetDuration() == EEffectDuration::Instant;

		FireEffect(Effects[I]);
	}
}

//
void UStatusEffectComponent::AddEffect(AStatusEffect* EffectToAdd)
{
	Effects.Add(EffectToAdd);

	FireEffect(EffectToAdd);
}


//
void UStatusEffectComponent::RemoveEffect(AStatusEffect* EffectToRemove)
{
	Effects.Remove(EffectToRemove);

	if (EffectToRemove->GetDuration() != EEffectDuration::Instant)
	{
		FireFinishEffect(EffectToRemove);
	}

	EffectToRemove->Destroy();
}


void UStatusEffectComponent::FireEffect(AStatusEffect* EffectToFire)
{
	auto EffectComposition = EffectToFire->GetEffectComposition();

	for (auto EffectUnit : EffectComposition)
	{
		OnEffectFire.Broadcast(EffectUnit.EffectTag, EffectUnit.EffectValue);
	}

	if (EffectToFire->GetDuration() == EEffectDuration::Instant)
	{
		RemoveEffect(EffectToFire);
	}
	else
	{
			//TODO set timer
	}
}


// Function called when effect is removed from component, in order to revert effect changes
void UStatusEffectComponent::FireFinishEffect(AStatusEffect* EffectToFire)
{
	auto EffectComposition = EffectToFire->GetEffectComposition();

	for (auto EffectUnit : EffectComposition)
	{
		FinishEffect.Broadcast(EffectUnit.EffectTag, EffectUnit.EffectValue* -1);
	}
}
