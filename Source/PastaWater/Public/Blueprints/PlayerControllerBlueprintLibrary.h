// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PastaWaterPlayerControllerBase.h"
#include "PlayerControllerBlueprintLibrary.generated.h"

/**
 * Helper methods for Player Controller management.
 */
UCLASS()
class PASTAWATER_API UPlayerControllerBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/**
	 * Clear out all current pressed keys.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	static void FlushInputs(APastaWaterPlayerControllerBase* PlayerController);

	/**
	 * Disallow any more inputs from occurring, i.e. looking, movement, actions.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	static void DisableAllInputs(APastaWaterPlayerControllerBase* PlayerController);

	/**
	 * Allow all inputs from occurring, used to reenable after using DisableAllInputs.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	static void EnableAllInputs(APastaWaterPlayerControllerBase* PlayerController);
};
