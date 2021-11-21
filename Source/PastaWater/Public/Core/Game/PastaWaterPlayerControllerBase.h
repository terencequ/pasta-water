// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "Core/Pawns/PastaWaterCharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "PastaWaterPlayerControllerBase.generated.h"

/**
 * Main player controller for a player in Pasta Water.
 */
UCLASS(NotBlueprintable)
class PASTAWATER_API APastaWaterPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category="Inventory Actor Components")
	APastaWaterCharacterBase* PastaWaterCharacter;
	
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool LookingEnabled = true;
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool MovementEnabled = true;
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool JumpActionEnabled = true;
	
	APastaWaterPlayerControllerBase();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnUnPossess() override;

public:
	static APastaWaterPlayerControllerBase* CastFromActor(AActor* Actor);

	static APastaWaterPlayerControllerBase* CastFromPlayerController(APlayerController* PlayerController);
	
	virtual void Tick(float DeltaTime) override;

	// Input bindings
	void PerformJumpAction();

	void PerformMoveRightLeft(float AxisValue);
	
	void PerformMoveForwardBackward(float AxisValue);

	void PerformLookPitch(float AxisValue);

	void PerformLookYaw(float AxisValue);

	// Input control
	/**
	 * Clear out all current pressed keys.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	void FlushInputs();

	/**
	 * Disallow any more inputs from occurring, i.e. looking, movement, actions.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	virtual void DisableAllInputs();

	/**
	 * Allow all inputs from occurring, used to reenable after using DisableAllInputs.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	virtual void EnableAllInputs();


protected:
	/**
	 * Toggle a widget's visibility.
	 */
	void ToggleWidgetVisibility(UWidget* Widget);

	/**
	 * Toggle a widget as the main focus of the player.
	 * When a widget is focused, the player will not be able to look or make movement inputs.
	 * The widget will be visible when focused, invisible when not.
	 */
	void ToggleWidgetVisibilityAndFocus(UWidget* Widget);
};
