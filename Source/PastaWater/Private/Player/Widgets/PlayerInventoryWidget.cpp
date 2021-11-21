#include "Player/Widgets/PlayerInventoryWidget.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Helpers/DebugHelpers.h"

UPlayerInventoryWidget* UPlayerInventoryWidget::Create(
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass,
	APastaWaterPlayerControllerBase* OwningPlayerController,
	UPlayerInventoryAC* OwningPlayerInventoryAC)
{
	// Create widget
	UPlayerInventoryWidget* PlayerInventoryWidget = CreateWidget<UPlayerInventoryWidget>(
		OwningPlayerController,
		PlayerInventoryWidgetClass,
		"Player Inventory");

	// Failure check
	if(!IsValid(PlayerInventoryWidget))
	{
		UDebugHelpers::ScreenLogError("Could not initialise Player Inventory Widget.");
		return nullptr;
	}

	// Setup widget and return
	UDebugHelpers::ScreenLogInfo("Initialised Player Inventory Widget.");
	PlayerInventoryWidget->Setup(OwningPlayerInventoryAC);
	PlayerInventoryWidget->CreateInventorySlots();
	PlayerInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerInventoryWidget->AddToViewport();
	return PlayerInventoryWidget;
}