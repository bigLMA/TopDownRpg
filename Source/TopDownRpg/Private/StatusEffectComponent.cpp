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
	int32 Index = 0;

	if(EnsureEffectStackable(EffectToAdd, Index))
	{
		Effects.Add(EffectToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT(" not added !!! %d"), Index)
		Effects[Index]->RefreshDuration();
		EffectToAdd->Destroy();
	}
										// TODO check for effect to cancel or cancelled by
	FireEffect(EffectToAdd);
}


// Returns true if effect is stackable or if no effects with similar class found
bool UStatusEffectComponent::EnsureEffectStackable(AStatusEffect* EffectToEnsure, int32& EffectIndex)
{
	if (EffectToEnsure->IsStackable()) { return true; }

	for (int32 Index = 0; Index<Effects.Num();++Index)
	{
		if (EffectToEnsure->GetClass() == Effects[Index]->GetClass())
		{
			EffectIndex = Index;
			return false;
		}
	}

	return true;
}


//
void UStatusEffectComponent::RemoveEffect(AStatusEffect* EffectToRemove)
{
	Effects.Remove(EffectToRemove);

	if (EffectToRemove->GetDuration() == EEffectDuration::Constant || EffectToRemove->GetDuration() == EEffectDuration::Duration&& EffectToRemove->GetEffectFiring()==EEffectFiring::Once)
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
	else if(EffectToFire->GetDuration() == EEffectDuration::Duration&& EffectToFire->GetEffectFiring() == EEffectFiring::PerTurn)
	{
		EffectToFire->SetDurationTimer();
		EffectToFire->OnFireEffect.AddUniqueDynamic(this, &UStatusEffectComponent::FireEffect);
		EffectToFire->OnFinishEffect.AddUniqueDynamic(this, &UStatusEffectComponent::RemoveEffect);
	}
	else if (EffectToFire->GetDuration() == EEffectDuration::Duration)
	{
		EffectToFire->SetDurationTimer();
		EffectToFire->OnFinishEffect.AddUniqueDynamic(this, &UStatusEffectComponent::RemoveEffect);
	}
}



void UStatusEffectComponent::LowerEffectDuration(AStatusEffect* Effect)
{

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
