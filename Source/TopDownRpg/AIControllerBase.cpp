// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AiCharacter.h"

AAIControllerBase::AAIControllerBase()
{
	BlackboardBase = CreateDefaultSubobject<UBlackboardComponent>("Blackboard Base");
}


void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();

	//ControlledCharacter = Cast<AAiCharacter>(GetPawn());
}


void AAIControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAIControllerBase::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ControlledCharacter = Cast<AAiCharacter>(InPawn);
	}
}


void AAIControllerBase::RunBT()
{
	if (!ensure(ControlledCharacter)) { return; }

	switch (ControlledCharacter->GetAttitude())
	{

	case EAttitudeTowardsPlayer::Hostile:
		RunBehaviorTree(FightLogic);
		return;

	case EAttitudeTowardsPlayer::Neutral:
			RunBehaviorTree(MainLogic);
			return;

	case EAttitudeTowardsPlayer::Under_Control:
			RunBehaviorTree(UnderPlayerControl);
			return;
	}

	return;
}


void AAIControllerBase::SetMoveValue(const FVector& Value)
{
	BlackboardBase->SetValueAsVector(("MovePoint"), Value);
}

