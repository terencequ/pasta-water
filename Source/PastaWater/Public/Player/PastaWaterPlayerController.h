#pragma once

#include "CoreMinimal.h"
#include "PlayerInteractorAC.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Widgets/PlayerInteractPromptWidget.h"
#include "Widgets/PlayerInventoryWidget.h"
#include "PastaWaterPlayerController.generated.h"

/**
 * Implementation of a basic player.
 */
UCLASS(Blueprintable)
class PASTAWATER_API APastaWaterPlayerController : public APastaWaterPlayerControllerBase
{
	GENERATED_BODY()

public:
	// Inputs
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool PrimaryActionEnabled = true;
	
	// Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Actor Components")
	UPlayerInventoryAC* PlayerInventoryAC;
	
	UPROPERTY(BlueprintReadWrite, Category="User Interface - Inventory")
	UPlayerInventoryWidget* PlayerInventoryWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Interface - Inventory")
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass;

	// Interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction Actor Components")
	UPlayerInteractorAC* PlayerInteractorAC;
	
	UPROPERTY(BlueprintReadWrite, Category="User Interface - Interaction")
	UPlayerInteractPromptWidget* InteractPromptWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Interface - Interaction")
	TSubclassOf<UPlayerInteractPromptWidget> InteractPromptWidgetClass;
	
	APastaWaterPlayerController();

	// Lifecycle
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	// Inputs
	void PerformToggleInventoryAction();
	
	void PerformPrimaryAction();
	
	virtual void EnableAllInputs() override;
	
	virtual void DisableAllInputs() override;
	
	// User Interface - Inventory
	void InitialiseInventoryUI();
	
	void ToggleInventoryUI();

	// User Interface - Interaction
	void InitialiseInteractPromptUI();
};
