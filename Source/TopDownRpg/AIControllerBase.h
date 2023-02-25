// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include"AIControllerBase.generated.h"

class AAiCharacter;

UCLASS()
class TOPDOWNRPG_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

private:
	virtual void SetPawn(APawn* InPawn) override;

protected:
	// This logic executes only when character attitude is Under_Control
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Logic|Under Player Control")
		UBehaviorTree* UnderPlayerControl;

	// This tree determines AI behaviour throut game (Quest giver, vendor, ETC)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Logic|Main Logic")
		UBehaviorTree* MainLogic = nullptr;

	// This tree determines AI behaviour during fight
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Logic|Fight Logic")
		UBehaviorTree* FightLogic = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI Logic|Blackboard")
	UBlackboardComponent* BlackboardBase = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "AI Logic|Controlled Character")
		AAiCharacter* ControlledCharacter = nullptr;
		
	UFUNCTION(BlueprintCallable, Category = "Run BT")
		void RunBT();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	AAIControllerBase();

	void SetMoveValue(const FVector& Value);
};
