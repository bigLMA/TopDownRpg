// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AiCharacter.generated.h"

class USelectionDecal;
class UStatsComponent;
class UStatusEffectComponent;

UENUM()
enum class EAttitudeTowardsPlayer :uint8
{
	Hostile, Neutral, Under_Control
};

UCLASS()
class TOPDOWNRPG_API AAiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAiCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Determines if character is player controlled and how he feels about player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Behaviour")
	EAttitudeTowardsPlayer AttitudeTowardsPlayer = EAttitudeTowardsPlayer::Neutral;

	// Character stats component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	UStatsComponent* Stats;

	// Character status effect component
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Status Effects")
	UStatusEffectComponent* StatusEffects;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when selected
	UFUNCTION(BlueprintImplementableEvent)
	void Selected(bool IsSelected);

	// Gets characters attitude towards player
	EAttitudeTowardsPlayer GetAttitude();
};
