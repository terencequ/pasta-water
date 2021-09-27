// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PastaWaterCharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "Interact/ActorComponents/PlayerInteractorAC.h"
#include "Inventory/ActorComponents/PlayerInventoryAC.h"
#include "Inventory/Widgets/PlayerInventoryWidget.h"
#include "PastaWaterPlayerControllerBase.generated.h"

/**
 * 
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
	
	UPROPERTY(BlueprintReadWrite)
	bool LookingEnabled = true;
	UPROPERTY(BlueprintReadWrite)
	bool MovementEnabled = true;
	UPROPERTY(BlueprintReadWrite)
	bool PrimaryActionEnabled = true;
	UPROPERTY(BlueprintReadWrite)
	bool JumpActionEnabled = true;

	UPROPERTY(BlueprintReadWrite)
	UPlayerInventoryWidget* PlayerInventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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

	void PerformJumpAction();

	void PerformPrimaryAction();
	
	void PerformToggleInventoryAction();

	void PerformMoveRightLeft(float AxisValue);
	
	void PerformMoveForwardBackward(float AxisValue);

	void PerformLookPitch(float AxisValue);

	void PerformLookYaw(float AxisValue);

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
	void ToggleWidgetFocus(UWidget* Widget);
};
