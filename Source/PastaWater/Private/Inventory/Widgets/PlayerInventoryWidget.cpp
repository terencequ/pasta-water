#include "Inventory/Widgets/PlayerInventoryWidget.h"

#include "PastaWaterPlayerControllerBase.h"
#include "Components/GridSlot.h"
#include "Helpers/DebugHelpers.h"
#include "Inventory/Widgets/ItemStackSlotWidget.h"

bool UPlayerInventoryWidget::CreateInventorySlots()
{
	APastaWaterPlayerControllerBase* PlayerController = GetOwningPastaPlayerController();
	UPlayerInventoryAC* PlayerInventoryAC = PlayerController->GetInventoryAC();
	UGridPanel* PlayerItemsGridPanel = GetItemsGridPanel();
	if(!IsValid(PlayerController) || !IsValid(PlayerItemsGridPanel) || !IsValid(PlayerInventoryAC))
	{
		return false;
	}
	
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
	const APastaWaterPlayerControllerBase* PlayerController = GetOwningPastaPlayerController();
	const UPlayerInventoryAC* PlayerInventoryAC = PlayerController->GetInventoryAC();
	const UGridPanel* PlayerItemsGridPanel = GetItemsGridPanel();
	if(!IsValid(PlayerController) || !IsValid(PlayerItemsGridPanel) || !IsValid(PlayerInventoryAC))
	{
		return false;
	}

	// Call "Update Item Details" on every item stack slot widget
	TArray<UWidget*> Widgets = PlayerItemsGridPanel->GetAllChildren();
	for(int Index = 0; Index < PlayerItemsGridPanel->GetChildrenCount(); Index++)
	{
		UItemStackSlotWidget* ItemStackSlot = Cast<UItemStackSlotWidget>(PlayerItemsGridPanel->GetChildAt(Index));
		ItemStackSlot->UpdateItemDetails();
	}
	
	return true;
}

APastaWaterPlayerControllerBase* UPlayerInventoryWidget::GetOwningPastaPlayerController() const
{
	APlayerController* PlayerController = GetOwningPlayer();
	if(!PlayerController)
	{
		UDebugHelpers::ScreenLogError("Inventory UI not owned by a Player Controller!");
		return nullptr;
	}
	
	APastaWaterPlayerControllerBase* PastaWaterPlayerController = Cast<APastaWaterPlayerControllerBase>(PlayerController);
	if(!PastaWaterPlayerController)
	{
		UDebugHelpers::ScreenLogInfo("Inventory UI needs to be owned by a Pasta Water Player Controller.");
		return nullptr;
	}

	return PastaWaterPlayerController;
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
