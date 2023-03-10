// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "CameraPawn.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;
class AAiCharacter;
class UInventoryComponent;

UCLASS()
class TOPDOWNRPG_API ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Display party inventory
	UFUNCTION(BlueprintImplementableEvent)
	void ToggleInventory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Setup")
		UFloatingPawnMovement* PawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Mapping Context")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Move")
	UInputAction* MoveCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Zoom")
	UInputAction* ZoomCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Zoom")
	float ZoomMin = 900.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Zoom")
	float ZoomMax = 2250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Zoom")
	float ZoomSpeed = -95.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Rotate")
	UInputAction* RotateCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Select")
	UInputAction* SelectUnit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Order")
	UInputAction* OrderUnit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Inventory")
	UInputAction* Inventory;

	UPROPERTY(BlueprintReadOnly, Category = "Selected Pawn")
		AAiCharacter* SelectedCharacter = nullptr;

private:
	// Move player camera
	void Move(const FInputActionValue& Value);

	// Zoom player camera
	void Zoom(const FInputActionValue& Value);

	// Rotate player camera
	void Rotate(const FInputActionValue& Value);

	// Select unit by mouse clicking
	void Select(const FInputActionValue& Value);

	// Issue order to selected unit 
	void Order(const FInputActionValue& Value);
};
