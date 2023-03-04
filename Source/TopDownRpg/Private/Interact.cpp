// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AiCharacter.h"
#include "AIController.h"

UInteract::UInteract(const FObjectInitializer& ObjectInitializer)
{
}

EBTNodeResult::Type UInteract::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	auto Controller = OwnerComp.GetAIOwner();

	if (AAiCharacter* ControlledCharacter = Cast<AAiCharacter>(Controller->GetPawn()))
	{
		// If the character interacts with another character
		if (AAiCharacter* InteractedObject = Cast<AAiCharacter>(Blackboard->GetValueAsObject(InteractedActor.SelectedKeyName)))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s interacts with %s"), *ControlledCharacter->GetName(), *InteractedObject->GetName())

			Blackboard->ClearValue(InteractedActor.SelectedKeyName);
		}	// if character interacts with item

		// If character interacts with container
	}

	return EBTNodeResult::Succeeded;
	//return EBTNodeResult::Type();
}
