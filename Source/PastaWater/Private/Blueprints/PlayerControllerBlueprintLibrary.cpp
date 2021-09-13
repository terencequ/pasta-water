// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprints/PlayerControllerBlueprintLibrary.h"

#include "PastaWaterPlayerControllerBase.h"
#include "GameFramework/PlayerInput.h"

void UPlayerControllerBlueprintLibrary::FlushInputs(APastaWaterPlayerControllerBase* PlayerController)
{
	if(PlayerController)
	{
		PlayerController->PlayerInput->FlushPressedKeys();
	}
}

void UPlayerControllerBlueprintLibrary::DisableAllInputs(APastaWaterPlayerControllerBase* PlayerController)
{
	if(PlayerController)
	{
		PlayerController->LookingEnabled = false;
		PlayerController->MovementEnabled = false;
		PlayerController->JumpActionEnabled = false;
		PlayerController->PrimaryActionEnabled = false;
	}
}

void UPlayerControllerBlueprintLibrary::EnableAllInputs(APastaWaterPlayerControllerBase* PlayerController)
{
	if(PlayerController)
	{
		PlayerController->LookingEnabled = true;
		PlayerController->MovementEnabled = true;
		PlayerController->JumpActionEnabled = true;
		PlayerController->PrimaryActionEnabled = true;
	}
}
