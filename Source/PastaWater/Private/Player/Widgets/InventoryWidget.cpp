#include "Player/Widgets/InventoryWidget.h"
#include "Components/GridSlot.h"

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

bool UInventoryWidget::OpenInventory()
{
	return true;
}

bool UInventoryWidget::CloseInventory()
{
	if(!IsValid(PlayerController) || !IsValid(InventoryAC))
		return false;

	// Move the mouse item stack back into the inventory
	const FItemStack MouseItemStack = IInventoryInterface::Execute_GetItemStackAtIndex(InventoryAC, -1);
	IInventoryInterface::Execute_InsertItemStack(InventoryAC, MouseItemStack);
	IInventoryInterface::Execute_SetItemStackAtIndex(InventoryAC, -1, FItemStack::Null());
	return true;
}

bool UInventoryWidget::CreateInventorySlots(const FString WidgetId)
{
	if(!IsValid(PlayerController) || !IsValid(InventoryAC))
		return false;
	
	// Add each item slot in inventory
	for(int Index = 0; Index < Columns*Rows; Index++)
	{
		FString ItemSlotWidgetId = WidgetId+FString(" Item Slot ")+FString::FromInt(Index+StartIndex);
		UItemStackSlotWidget* Widget = CreateWidget<UItemStackSlotWidget>(PlayerController, ItemStackSlotClass, FName(*ItemSlotWidgetId));
		if(IsValid(Widget))
		{
			Widget->InventoryAC = InventoryAC;
			Widget->InventoryACIndex = Index + StartIndex;
			Widget->SetVisibility(ESlateVisibility::Visible);
			Widget->AddToViewport();

			// Add to items grid panel
			const int Row = Index / Columns;
			const int Column = Index % Columns;
			UGridSlot* GridSlot = ItemsGridPanel->AddChildToGrid(Widget, Row, Column);
			GridSlot->SetPadding(FMargin(8));
		}
	}
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
	
	return true;
}

void UInventoryWidget::OnCloseInventory()
{
	CloseInventory();
}

void UInventoryWidget::OnUpdateInventorySlots(const TArray<FItemStack> ItemStacks)
{
	UpdateInventorySlots();
}
