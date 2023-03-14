// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Components/BoxComponent.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ActorRootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(ActorRootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static mesh");
	StaticMesh->SetupAttachment(ActorRootComponent);

	Collision = CreateDefaultSubobject< UBoxComponent>("Collision");
	Collision->SetupAttachment(ActorRootComponent);
}


// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
}


// Called when character interacts with character
void AInteractableActor::Interact_Implementation()
{
	InteractInternal();
}


// Internal implementation for interact
void AInteractableActor::InteractInternal()
{

}
