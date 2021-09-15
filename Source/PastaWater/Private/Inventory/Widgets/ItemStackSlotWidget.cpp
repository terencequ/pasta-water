#include "Inventory/Widgets/ItemStackSlotWidget.h"

#include "Helpers/DebugHelpers.h"

bool UItemStackSlotWidget::Initialize()
{
	const bool Success = Super::Initialize();
	return Success;
}

void UItemStackSlotWidget::UpdateItemDetails()
{
	const FItemStack ItemStack = GetItemDetails();

	// Set Item Name text
	const FString ItemNameString = ItemStack.IsNull() ? "" : ItemStack.Item.Name;
	if(ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(ItemNameString));
	} else
	{
		UDebugHelpers::ScreenLogError("Item Name Text is not valid!");
	}
	
	// Set Item Quantity text
	const FString ItemQuantityString = ItemStack.IsNull() ? "" : FString::FromInt(ItemStack.Quantity);
	if(ItemQuantityText)
	{
		ItemQuantityText->SetText(FText::FromString(ItemQuantityString));
	} else
	{
		UDebugHelpers::ScreenLogError("Item Name Text is not valid!");
	}

	// TODO: Item icon
}

FItemStack UItemStackSlotWidget::GetItemDetails() const
{
	if(!InventoryAC.GetObject())
	{
		UDebugHelpers::ScreenLogWarning("Inventory does not exist.");
		return FItemStack::Null();
	}
	
	FItemStack Stack = IInventoryACInterface::Execute_GetItemStackAtIndex(
		InventoryAC.GetObject(),
		InventoryACIndex);
	return Stack;
}
