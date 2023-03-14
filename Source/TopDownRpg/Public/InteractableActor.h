// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

class UBoxComponent;

UCLASS()
class TOPDOWNRPG_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

	// Called when character interacts with character
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Root")
	USceneComponent* ActorRootComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Static mesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	UBoxComponent* Collision;

	// Internal implementation for interact
	virtual void InteractInternal();
};
