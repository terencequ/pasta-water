// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprints/PlayerControllerBlueprintLibrary.h"

#include "PastaWaterPlayerControllerBase.h"
#include "GameFramework/PlayerInput.h"

void UPlayerControllerBlueprintLibrary::FlushInputs(APastaWaterPlayerControllerBase* PlayerController)
{
	PlayerController->PlayerInput->FlushPressedKeys();
}

void UPlayerControllerBlueprintLibrary::DisableAllInputs(APastaWaterPlayerControllerBase* PlayerController)
{
	PlayerController->SetIgnoreMoveInput(true);
	PlayerController->SetIgnoreLookInput(true);
}

void UPlayerControllerBlueprintLibrary::EnableAllInputs(APastaWaterPlayerControllerBase* PlayerController)
{
	PlayerController->SetIgnoreMoveInput(false);
	PlayerController->SetIgnoreLookInput(false);
}
