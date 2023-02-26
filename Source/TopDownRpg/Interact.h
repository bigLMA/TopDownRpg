// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Interact.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UInteract : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UInteract(const FObjectInitializer& ObjectInitializer);

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector InteractedActor;

};
