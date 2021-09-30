#include "Player/Widgets/PlayerInventoryWidget.h"
#include "Components/GridSlot.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Helpers/DebugHelpers.h"

UPlayerInventoryWidget* UPlayerInventoryWidget::Create(
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass,
	APastaWaterPlayerControllerBase* OwningPlayerController,
	TScriptInterface<IInventoryInterface> OwningPlayerInventoryAC)
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
	PlayerInventoryWidget->Initialise(OwningPlayerController, OwningPlayerInventoryAC);
	PlayerInventoryWidget->CreateInventorySlots();
	PlayerInventoryWidget->UpdateInventorySlots();
	PlayerInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	PlayerInventoryWidget->AddToViewport();
	return PlayerInventoryWidget;
}

bool UPlayerInventoryWidget::Initialise(APastaWaterPlayerControllerBase* OwningPlayerController, TScriptInterface<IInventoryInterface>& OwningPlayerInventoryAC)
{
	// Get dependent variables
	if(!IsValid(GetOwningPlayer()))
		return false;
	
	PlayerController = OwningPlayerController;
	if(!IsValid(PlayerController))
		return false;
	
	InventoryAC = OwningPlayerInventoryAC;
	if(!IsValid(InventoryAC.GetObject()))
		return false;
	
	PlayerItemsGridPanel = GetItemsGridPanel();
	if(!IsValid(PlayerItemsGridPanel))
		return false;
	
	return true;
}

bool UPlayerInventoryWidget::CreateInventorySlots()
{
	if(!IsValid(PlayerController) || !IsValid(InventoryAC.GetObject()) || !IsValid(PlayerItemsGridPanel))
		return false;
	
	// Add each item slot in inventory
	for(int Index = 0; Index < Columns*Rows; Index++)
	{
		UItemStackSlotWidget* Widget = CreateWidget<UItemStackSlotWidget>(PlayerController, ItemStackSlotClass, "Item Stack Slot "+Index);
		if(IsValid(Widget))
		{
			Widget->InventoryAC = InventoryAC;
			Widget->InventoryACIndex = Index;
			Widget->SetVisibility(ESlateVisibility::Visible);
			Widget->AddToViewport();

			// Add to items grid panel
			const int Row = Index / Columns;
			const int Column = Index % Columns;
			UGridSlot* GridSlot = PlayerItemsGridPanel->AddChildToGrid(Widget, Row, Column);
			GridSlot->SetPadding(FMargin(10));
		}
	}

	return true;
}

bool UPlayerInventoryWidget::UpdateInventorySlots()
{
	if(!IsValid(PlayerController) || !IsValid(InventoryAC.GetObject()) || !IsValid(PlayerItemsGridPanel))
		return false;

	// Call "Update Item Details" on every item stack slot widget
	TArray<UWidget*> Widgets = PlayerItemsGridPanel->GetAllChildren();
	for(int Index = 0; Index < PlayerItemsGridPanel->GetChildrenCount(); Index++)
	{
		UItemStackSlotWidget* ItemStackSlot = Cast<UItemStackSlotWidget>(PlayerItemsGridPanel->GetChildAt(Index));
		ItemStackSlot->UpdateItemDetails();
	}

	UDebugHelpers::ScreenLogInfo("Player Inventory UI updated.");
	return true;
}

UGridPanel* UPlayerInventoryWidget::GetItemsGridPanel() const
{
	if(!ItemsGridPanel)
	{
		UDebugHelpers::ScreenLogError("Player Inventory's main item grid panel is not initialised!");
		return nullptr;
	}

	return ItemsGridPanel;
}
