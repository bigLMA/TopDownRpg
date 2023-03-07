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
}


//
TArray<FEffectComposition> AStatusEffect::GetEffectComposition() const
{
	return EffectComposition;
}



EEffectDuration AStatusEffect::GetDuration() const
{
	return EffectDuration;
}

EEffectFiring AStatusEffect::GetEffectFiring() const
{
	return EffectFiring;
}



int32 AStatusEffect::GetCurrentDuration() const
{
	return CurrentDuration;
}


//
void AStatusEffect::SetDurationTimer()
{

	if (true)
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &AStatusEffect::DecreaseDuration, SecondsPerTurn, true);
	}
	else		//TODO for turn based
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}


//
void AStatusEffect::DecreaseDuration()
{
	--BaseDuration;

	if(EffectDuration == EEffectDuration::Duration&& EffectFiring == EEffectFiring::PerTurn|| BaseDuration<=0)
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);

		if (BaseDuration > 0)
		{
			OnFireEffect.Broadcast(this);
		}
		else
		{
			OnFinishEffect.Broadcast(this);
		}
	}
}



void AStatusEffect::RefreshDuration()
{
	CurrentDuration = BaseDuration;
}



bool AStatusEffect::IsStackable()
{
	return bIsStackable;
}


FGameplayTagContainer AStatusEffect::GetCancelTags()
{
	return CancelTags;
}


FGameplayTagContainer AStatusEffect::GetTagsToCancel()
{
	return TagsToCancel;
}

