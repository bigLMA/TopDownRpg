// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "AiCharacter.h"
#include "StatsComponent.h"
#include "StatusEffectComponent.h"
#include "StatusEffect.h"
#include "Animation/AnimMontage.h"


// Sets default values
AAbilityBase::AAbilityBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


// Called when the game starts or when spawned
void AAbilityBase::BeginPlay()
{
	Super::BeginPlay();

}


// Prepares ability to cast, allowing player to choose cast target, area etc
void AAbilityBase::PrepareAbility()
{	// Check energy
	if (IsAbilityOnCooldown()) { return; }

	// spawn ability show actor

	// wait until player confirmes ability activation
	
		// or cancel ability preparation
}


// Starts ability to behave, starts cooldown, animation etc
void AAbilityBase::ActivateAbility()
{
	SetAbilityOnCooldown();
	PlayAnimation();
}


// Play ability animation
void AAbilityBase::PlayAnimation()
{
	AbilityCaster->PlayAnimMontage(AbilityMontage);
}


// Implementable event for cast on blueprints
void AAbilityBase::CastAbility_Implementation()
{
	CastAbilityInternal();
}


// Applies ability effects on target
void AAbilityBase::CastAbilityInternal()
{
	UE_LOG(LogTemp, Warning, TEXT("Appying effects"))
}


// Set character who casts ability
void AAbilityBase::SetAbilityCaster(AAiCharacter* Target)
{
	AbilityCaster = Target;
}


// Add ability target (sets if target is single)
void AAbilityBase::AddAbilityTarget(AActor* Target)
{
	AbilityTargets.Add(Target);
}


// Make ability unable to cast during cooldown
void AAbilityBase::SetAbilityOnCooldown()	//TODO for turn based
{
	CurrentCooldown = AbilityCooldown;

	// Check if turn based
	if (true)
	{
		// Decrease by timer if real time 
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &AAbilityBase::DecreaseCooldown, SecondsPerTurn, true, SecondsPerTurn);
	}
	else
	{
		// Otherwise stop timer and wait for manual decreasment
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		//DecreaseCooldown();
	}
}


// Decrease cooldown value
void AAbilityBase::DecreaseCooldown()
{
	--CurrentCooldown;

	// if cooldown value is 0
	if (CurrentCooldown<1)
	{
		// Remove timer
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}


// Returns if ability is on cooldown
bool AAbilityBase::IsAbilityOnCooldown()
{
	return CurrentCooldown>0;
}



// Returns current cooldown value
int32 AAbilityBase::GetCurrentCooldown()
{
	return CurrentCooldown;
}


// Calculates if ability reaches target actors
bool AAbilityBase::CalculateAbilityChance()
{
	if (BaseChance == 100)
	{
		return true;
	}
	else
	{
		return false;		// TODO if base chance + caster skill - target ability defence >= FMath::RandRange(1, 100);
	}
}