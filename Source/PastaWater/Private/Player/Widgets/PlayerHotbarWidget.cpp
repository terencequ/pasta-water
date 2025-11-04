// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Widgets/PlayerHotbarWidget.h"

#include "Components/CanvasPanelSlot.h"
#include "Core/Helpers/DebugHelpers.h"


void UPlayerHotbarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UPlayerInventoryAC* OwningInventoryAC = Cast<UPlayerInventoryAC>(InventoryAC);
	if (!OwningInventoryAC)
	{
		return;
	}
	
	// Set up hotbar delegates
	OwningInventoryAC->UpdateHotbarSelectionDelegate.AddUObject(
		this,
		&UPlayerHotbarWidget::OnUpdateHotbarSelection);
}

bool UPlayerHotbarWidget::CreateInventorySlots(const FString WidgetId)
{
	return Super::CreateInventorySlots(WidgetId);
}

bool UPlayerHotbarWidget::UpdateInventorySlots()
{
	return Super::UpdateInventorySlots();
}

void UPlayerHotbarWidget::OnUpdateHotbarSelection(int CurrentSelectedHotbarIndex)
{
	UDebugHelpers::ScreenLogInfo("Updating hotbar selection to index: " + FString::FromInt(CurrentSelectedHotbarIndex));

	// Highlight selected hotbar slot by moving the hotbar highlighter image to the position of the selected slot
	if (!IsValid(HotbarHighlighter) || !IsValid(ItemsGridPanel))
	{
		return;
	}


	UWidget* ChildWidget = ItemsGridPanel->GetChildAt(CurrentSelectedHotbarIndex);
	if (!IsValid(ChildWidget))
	{
		UDebugHelpers::ScreenLogError(
			"Could not find child widget at index: " + FString::FromInt(CurrentSelectedHotbarIndex));
		return;
	}

	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(HotbarHighlighter->Slot);
	if (!IsValid(CanvasPanelSlot))
	{
		UDebugHelpers::ScreenLogError("Cannot find Canvas Panel Slot for Hotbar Highlighter movement.");
		return;
	}

	// Get geometry for both widgets
	const FGeometry& CanvasGeometry = HotbarHighlighter->GetParent()->GetCachedGeometry();
	const FGeometry& ChildGeometry = ChildWidget->GetCachedGeometry();

	// Convert the child's absolute position into the canvas panel's local space
	FVector2D ChildAbsolute = ChildGeometry.GetAbsolutePosition();
	FVector2D LocalToCanvas = CanvasGeometry.AbsoluteToLocal(ChildAbsolute);

	// Optionally, adjust for alignment or padding
	CanvasPanelSlot->SetPosition(LocalToCanvas);

	UDebugHelpers::ScreenLogInfo(
		FString::Printf(TEXT("Moved highlighter to local pos: X=%f, Y=%f"), LocalToCanvas.X, LocalToCanvas.Y)
	);
}


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
	if (!IsValid(PlayerHotbarWidget))
	{
		UDebugHelpers::ScreenLogError("Could not initialise Player Hotbar Widget.");
		return nullptr;
	}

	// Setup widget and return
	UDebugHelpers::ScreenLogInfo("Initialised Player Hotbar Widget.");
	PlayerHotbarWidget->Setup(OwningPlayerInventoryAC);
	PlayerHotbarWidget->CreateInventorySlots("Hotbar");
	PlayerHotbarWidget->UpdateInventorySlots();
	PlayerHotbarWidget->SetVisibility(ESlateVisibility::Visible);
	PlayerHotbarWidget->AddToViewport();
	return PlayerHotbarWidget;
}
