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
	for (auto Effect : Effects)
	{
		FireEffect(Effect);
	}
	//for (int32 I = 0; I<Effects.Num(); ++I)
	//{
	//	FireEffect(Effects[I]);
	//}
}

//
void UStatusEffectComponent::AddEffect(AStatusEffect* EffectToAdd)
{
	Effects.Add(EffectToAdd);

	FireEffect(EffectToAdd);

	//TODO tick effect and set timer
	//for (auto Effect : EffectToAdd->GetEffectContainers())
	//{

	//}
}


//
void UStatusEffectComponent::RemoveEffect(AStatusEffect* EffectToRemove)
{

}


void UStatusEffectComponent::FireEffect(AStatusEffect* EffectToFire)
{
	auto EffectComposition = EffectToFire->GetEffectComposition();

	for (auto EffectUnit : EffectComposition)
	{
		OnEffectFire.Broadcast(EffectUnit.EffectTag, EffectUnit.EffectValue);
	}
}
