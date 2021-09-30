#pragma once

#include "CoreMinimal.h"
#include "PlayerInteractorAC.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "PastaWaterPlayerController.generated.h"

/**
 * Implementation of a basic player.
 */
UCLASS()
class PASTAWATER_API APastaWaterPlayerController : public APastaWaterPlayerControllerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Actor Components")
	UPlayerInventoryAC* PlayerInventoryAC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction Actor Components")
	UPlayerInteractorAC* PlayerInteractorAC;
	
	UPROPERTY(BlueprintReadWrite, Category="Input Toggle")
	bool PrimaryActionEnabled = true;

	UPROPERTY(BlueprintReadWrite, Category="User Interface")
	UPlayerInventoryWidget* PlayerInventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="User Interface")
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass;

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
	
	// Inventory
	void InitialiseInventory();
	
	void ToggleInventory();
};
