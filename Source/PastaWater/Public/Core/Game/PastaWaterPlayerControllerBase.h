// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Pawns/PastaWaterCharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "Player/PlayerInteractorAC.h"
#include "Player/PlayerInventoryAC.h"
#include "Player/Widgets/PlayerInventoryWidget.h"
#include "PastaWaterPlayerControllerBase.generated.h"

/**
 * Main player controller for a player in Pasta Water.
 */
UCLASS()
class PASTAWATER_API APastaWaterPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category="Inventory Actor Components")
	APastaWaterCharacterBase* PastaWaterCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Actor Components")
	UPlayerInventoryAC* PlayerInventoryAC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction Actor Components")
	UPlayerInteractorAC* PlayerInteractorAC;
	
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool LookingEnabled = true;
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool MovementEnabled = true;
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool PrimaryActionEnabled = true;
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool JumpActionEnabled = true;

	UPROPERTY(BlueprintReadWrite, Category="User Interface")
	UPlayerInventoryWidget* PlayerInventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Interface")
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass;
	
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

	void PerformPrimaryAction();
	
	void PerformToggleInventoryAction();

	void PerformMoveRightLeft(float AxisValue);
	
	void PerformMoveForwardBackward(float AxisValue);

	void PerformLookPitch(float AxisValue);

	void PerformLookYaw(float AxisValue);

	// Input control
	/**
	 * Get Inventory Actor Component with null check.
	 */
	UPlayerInventoryAC* GetInventoryACOrDefault() const;

	/**
	 * Clear out all current pressed keys.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	void FlushInputs();

	/**
	 * Disallow any more inputs from occurring, i.e. looking, movement, actions.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	void DisableAllInputs();

	/**
	 * Allow all inputs from occurring, used to reenable after using DisableAllInputs.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	void EnableAllInputs();
	
	// Inventory GUI
	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void InitialiseInventory();

	UFUNCTION(BlueprintCallable, Client, Unreliable)
	void ToggleInventory();
	
private:
	/**
	 * Toggle a widget as the main focus of the player.
	 * When a widget is focused, the player will not be able to look or make movement inputs.
	 */
	void ToggleWidgetFocus(UWidget* Widget);

	// Input Helpers

};
