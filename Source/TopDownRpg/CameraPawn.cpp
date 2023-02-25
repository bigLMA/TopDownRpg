// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "AiCharacter.h"
#include "AIControllerBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject< USceneComponent>("Root");
	SetRootComponent(Root);

	SpringArm = CreateDefaultSubobject< USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	PawnMovement = CreateDefaultSubobject< UFloatingPawnMovement>("Pawn Movement");
}


// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast< APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}


// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = CastChecked< UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveCamera, ETriggerEvent::Triggered, this, &ACameraPawn::Move);
		EnhancedInput->BindAction(ZoomCamera, ETriggerEvent::Triggered, this, &ACameraPawn::Zoom);
		EnhancedInput->BindAction(RotateCamera, ETriggerEvent::Triggered, this, &ACameraPawn::Rotate);
		EnhancedInput->BindAction(SelectUnit, ETriggerEvent::Triggered, this, &ACameraPawn::Select);
		EnhancedInput->BindAction(OrderUnit, ETriggerEvent::Triggered, this, &ACameraPawn::Order);
	}
}


void ACameraPawn::Move(const FInputActionValue& Value)
{
	auto MoveValue = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MoveValue.X);
	AddMovementInput(GetActorRightVector(), MoveValue.Y);
}


void ACameraPawn::Zoom(const FInputActionValue& Value)
{
	auto ZoomValue = Value.Get<float>();

	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, ZoomMin, ZoomMax);
	SpringArm->TargetArmLength += ZoomValue * ZoomSpeed;
}


void ACameraPawn::Rotate(const FInputActionValue& Value)
{
	auto RotateValue = Value.Get<float>();

	SetActorRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + RotateValue, GetActorRotation().Roll));
}


void ACameraPawn::Select(const FInputActionValue& Value)
{
	auto Selection = Value.Get<bool>();

	if(SelectedCharacter)
	{
		SelectedCharacter->Selected(false);
		SelectedCharacter = nullptr;
	}

	if(Selection)
	{
		FHitResult HitResult;

		if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery3, true, HitResult))
		{
			if (AAiCharacter* Character = Cast<AAiCharacter>(HitResult.GetActor()))
			{
				SelectedCharacter = Character;
				SelectedCharacter->Selected(true);
			}
		}
	}
}


void ACameraPawn::Order(const FInputActionValue& Value)
{
	auto Ordering = Value.Get<bool>();

	if (Ordering && SelectedCharacter)
	{

		AAIControllerBase* SelectedCharacterController = Cast< AAIControllerBase>(UAIBlueprintHelperLibrary::GetAIController(SelectedCharacter));

		TArray<TEnumAsByte<EObjectTypeQuery>> Array;
		Array.Add(EObjectTypeQuery::ObjectTypeQuery7);
		FHitResult HitResult;

		if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(Array, true, HitResult)&& Controller)
		{
			SelectedCharacterController->SetMoveValue(HitResult.Location);
		}
	}
}

