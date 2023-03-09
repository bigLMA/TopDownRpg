// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityBase.h"
#include "AiCharacter.h"
#include "StatsComponent.h"
#include "StatusEffectComponent.h"
#include "StatusEffect.h"


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



void AAbilityBase::PrepareAbility()
{
	if (IsAbilityOnCooldown()) { return; }

	// spawn ability show actor

	// wait until player confirmes ability activation
	
		// or cancel ability preparation
}


// 
void AAbilityBase::ActivateAbility()
{
	SetAbilityOnCooldown();
	PlayAnimation();
}



void AAbilityBase::CastAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("After anim function"))
}


void AAbilityBase::SetAbilityCaster(AAiCharacter* Target)
{
	AbilityCaster = Target;
}


void AAbilityBase::AddAbilityTarget(AAiCharacter* Target)
{
	AbilityTargets.Add(Target);
}



void AAbilityBase::SetAbilityOnCooldown()	//TODO for turn based
{
	CurrentCooldown = AbilityCooldown;

	if (true)
	{
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &AAbilityBase::DecreaseCooldown, SecondsPerTurn, true, SecondsPerTurn);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
		DecreaseCooldown();
	}
}



void AAbilityBase::DecreaseCooldown()
{
	--CurrentCooldown;

	if (CurrentCooldown<1)	//TODO for turn based
	{
		GetWorld()->GetTimerManager().ClearTimer(Timer);
	}
}



bool AAbilityBase::IsAbilityOnCooldown()
{
	return CurrentCooldown>0;

	
}



int32 AAbilityBase::GetCurrentCooldown()
{
	return CurrentCooldown;
}



bool AAbilityBase::CalculateAbilityChance()
{
	if (BaseChance == 100)
	{
		return true;
	}
	else
	{
		return false;		// if base chance + caster skill - target ability defence >= FMath::RandRange(1, 100);
	}
}
	


	
