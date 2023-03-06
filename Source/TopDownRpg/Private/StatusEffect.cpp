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
TArray<FEffectComposition> AStatusEffect::GetEffectComposition()
{
	return EffectComposition;
}


EEffectDuration AStatusEffect::GetDuration()
{
	return EffectDuration;
}

