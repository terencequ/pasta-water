#include "Inventory/Widgets/PlayerInventoryWidget.h"

#include "PastaWaterPlayerControllerBase.h"
#include "Components/GridSlot.h"
#include "Helpers/DebugHelpers.h"
#include "Inventory/Widgets/ItemStackSlotWidget.h"

bool UPlayerInventoryWidget::Initialise()
{
	// Get dependent variables
	if(!IsValid(GetOwningPlayer()))
		return false;
	
	PlayerController = APastaWaterPlayerControllerBase::CastFromPlayerController(GetOwningPlayer());
	if(!IsValid(PlayerController))
		return false;
	
	PlayerInventoryAC = PlayerController->GetInventoryACOrDefault();
	if(!IsValid(PlayerInventoryAC))
		return false;
	
	PlayerItemsGridPanel = GetItemsGridPanel();
	if(!IsValid(PlayerItemsGridPanel))
		return false;
	
	return true;
}

bool UPlayerInventoryWidget::CreateInventorySlots()
{
	if(!IsValid(PlayerController) || !IsValid(PlayerInventoryAC) || !IsValid(PlayerItemsGridPanel))
		return false;
	
	// Add each item slot in inventory
	for(int Index = 0; Index < Columns*Rows; Index++)
	{
		UItemStackSlotWidget* Widget = CreateWidget<UItemStackSlotWidget>(PlayerController, ItemStackSlotClass, "Item Stack Slot "+Index);
		if(IsValid(Widget))
		{
			Widget->InventoryAC = PlayerInventoryAC;
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
	if(!IsValid(PlayerController) || !IsValid(PlayerInventoryAC) || !IsValid(PlayerItemsGridPanel))
		return false;

	// Call "Update Item Details" on every item stack slot widget
	TArray<UWidget*> Widgets = PlayerItemsGridPanel->GetAllChildren();
	for(int Index = 0; Index < PlayerItemsGridPanel->GetChildrenCount(); Index++)
	{
		UItemStackSlotWidget* ItemStackSlot = Cast<UItemStackSlotWidget>(PlayerItemsGridPanel->GetChildAt(Index));
		ItemStackSlot->UpdateItemDetails();
	}
	
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
