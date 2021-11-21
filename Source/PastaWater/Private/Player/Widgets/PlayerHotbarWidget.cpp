// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Widgets/PlayerHotbarWidget.h"

#include "Core/Helpers/DebugHelpers.h"

UPlayerHotbarWidget* UPlayerHotbarWidget::Create(
	TSubclassOf<UPlayerHotbarWidget> PlayerInventoryWidgetClass,
	APastaWaterPlayerControllerBase* OwningPlayerController,
	UPlayerInventoryAC* OwningPlayerInventoryAC)
{
	// Create widget
	UPlayerHotbarWidget* PlayerHotbarWidget = CreateWidget<UPlayerHotbarWidget>(
		OwningPlayerController,
		PlayerInventoryWidgetClass,
		"Player Hotbar");

	// Failure check
	if(!IsValid(PlayerHotbarWidget))
	{
		UDebugHelpers::ScreenLogError("Could not initialise Player Hotbar Widget.");
		return nullptr;
	}

	// Setup widget and return
	UDebugHelpers::ScreenLogInfo("Initialised Player Hotbar Widget.");
	PlayerHotbarWidget->Setup(OwningPlayerInventoryAC);
	PlayerHotbarWidget->CreateInventorySlots();
	PlayerHotbarWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerHotbarWidget->AddToViewport();
	return PlayerHotbarWidget;
}
