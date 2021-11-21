#include "Player/Widgets/InventoryWidget.h"

#include "Components/GridSlot.h"
#include "Core/Helpers/DebugHelpers.h"

bool UInventoryWidget::Setup(UInventoryACBase* OwningInventoryAC)
{
	// Get dependent variables
	PlayerController = Cast<APastaWaterPlayerControllerBase>(GetOwningPlayer());
	if(!IsValid(PlayerController))
		return false;
	
	InventoryAC = OwningInventoryAC;
	if(!IsValid(InventoryAC))
		return false;

	InventoryAC->UpdateInventoryDelegate.AddUObject(this, &UInventoryWidget::OnUpdateInventorySlots);
	return true;
}

bool UInventoryWidget::CreateInventorySlots()
{
	if(!IsValid(PlayerController) || !IsValid(InventoryAC))
		return false;
	
	// Add each item slot in inventory
	for(int Index = StartIndex; Index < Columns*Rows+StartIndex; Index++)
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
			UGridSlot* GridSlot = ItemsGridPanel->AddChildToGrid(Widget, Row, Column);
			GridSlot->SetPadding(FMargin(10));
		}
	}

	OnUpdateInventorySlots(IInventoryInterface::Execute_GetAllItemStacks(InventoryAC));
	return true;
}

bool UInventoryWidget::UpdateInventorySlots()
{
	if(!IsValid(PlayerController) || !IsValid(InventoryAC))
		return false;

	// Call "Update Item Details" on every item stack slot widget
	TArray<UWidget*> Widgets = ItemsGridPanel->GetAllChildren();
	for(int Index = 0; Index < ItemsGridPanel->GetChildrenCount(); Index++)
	{
		UItemStackSlotWidget* ItemStackSlot = Cast<UItemStackSlotWidget>(ItemsGridPanel->GetChildAt(Index));
		ItemStackSlot->UpdateItemDetails();
	}

	UDebugHelpers::ScreenLogInfo("Player Inventory UI updated.");
	return true;
}

void UInventoryWidget::OnUpdateInventorySlots(const TArray<FItemStack> ItemStacks)
{
	UpdateInventorySlots();
}
