// Fill out your copyright notice in the Description page of Project Settings.


#include "AiCharacter.h"
#include "StatsComponent.h"
#include "StatusEffectComponent.h"
#include "AbilitiesComponent.h"

// Sets default values
AAiCharacter::AAiCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Stats = CreateDefaultSubobject<UStatsComponent>("Stats");

	StatusEffects = CreateDefaultSubobject<UStatusEffectComponent>("Status Effects");

	AbilitiesComponent = CreateDefaultSubobject<UAbilitiesComponent>("Abilities");
}

// Called when the game starts or when spawned
void AAiCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Gets characters attitude towards player
EAttitudeTowardsPlayer AAiCharacter::GetAttitude()
{
	return AttitudeTowardsPlayer;
}

