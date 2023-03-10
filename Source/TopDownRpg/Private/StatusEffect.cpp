// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"

// Sets default values
AStatusEffect::AStatusEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


// Called when the game starts or when spawned
void AStatusEffect::BeginPlay()
{
	Super::BeginPlay();

	RefreshDuration();
}


// Gets all values to change in effect
TArray<FEffectComposition> AStatusEffect::GetEffectComposition() const
{
	return EffectComposition;
}


// Gets effect duration
EEffectDuration AStatusEffect::GetDuration() const
{
	return EffectDuration;
}


// Gets effect firing
EEffectFiring AStatusEffect::GetEffectFiring() const
{
	return EffectFiring;
}


// Gets current effect duration remaining
int32 AStatusEffect::GetCurrentDuration() const
{
	return CurrentDuration;
}


// Start timer (if realtime) to to decrease effect duration
void AStatusEffect::SetDurationTimer()
{
	// Check if turn based
	if (true)
	{
		//Enable timer
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &AStatusEffect::DecreaseDuration, SecondsPerTurn, true);
	}
	else		//TODO for turn based
	{
		// Disable timer
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		//DecreaseDuration();
	}
}


// Decrease  duration value
void AStatusEffect::DecreaseDuration()
{
	--CurrentDuration;

	// If effect is durational and fires per turn or duration is 0
	if(EffectDuration == EEffectDuration::Duration&& EffectFiring == EEffectFiring::PerTurn|| CurrentDuration <=0)
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);

		if (CurrentDuration > 0)
		{
			// Fire effect
			OnFireEffect.Broadcast(this);
		}
		else
		{
			// Fire effect last time and finish effect
			OnFireEffect.Broadcast(this);	
			OnFinishEffect.Broadcast(this);
		}
	}
}


// Sets effect duration
void AStatusEffect::RefreshDuration()
{
	CurrentDuration = BaseDuration;
}


// Returns if effect stacks
bool AStatusEffect::IsStackable()
{
	return bIsStackable;
}
