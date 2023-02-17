// Copyright Epic Games, Inc. All Rights Reserved.

#include "TopDownRpgGameMode.h"
#include "TopDownRpgPlayerController.h"
#include "TopDownRpgCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATopDownRpgGameMode::ATopDownRpgGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownRpgPlayerController::StaticClass();
}