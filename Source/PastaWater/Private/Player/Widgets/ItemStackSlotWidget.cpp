#include "Player/Widgets/ItemStackSlotWidget.h"

#include "Core/Game/PastaWaterGameState.h"
#include "Core/Helpers/DebugHelpers.h"

bool UItemStackSlotWidget::Initialize()
{
	const bool Success = Super::Initialize();
	ItemButton->OnClicked.AddDynamic(this, &UItemStackSlotWidget::OnClick); 
	return Success;
}

void UItemStackSlotWidget::UpdateItemDetails()
{
	const FItemStack ItemStack = GetItemDetails();

	// Set Item Name text
	const APastaWaterGameState* PastaWaterGameState = APastaWaterGameState::GetGameState(this);
	if(!IsValid(PastaWaterGameState)){return;}
	const FItem* Item = PastaWaterGameState->FindItem(ItemStack.ItemId);
	const FString ItemName = ItemStack.IsNull() ? "" : Item->Name;
	
	if(ItemNameText)
	{
		ItemNameText->SetText(FText::FromString(ItemName));
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

	// Set Item icon
	UTexture2D* ItemTexture = nullptr;
	if(!ItemStack.IsNull())
	{
		const FString ItemPath = FString("/Game/PastaWater/Assets/Textures/Items/") + ItemStack.ItemId;
		ItemTexture = LoadObject<UTexture2D>(nullptr, *ItemPath, nullptr, LOAD_None, nullptr);
	}

	if(ItemImage)
	{
		if(IsValid(ItemTexture))
		{
			ItemImage->SetOpacity(1.0f);
			ItemImage->SetBrushFromTexture(ItemTexture, true);
		} else
		{
			ItemImage->SetOpacity(0.0f);
			ItemImage->SetBrushFromTexture(nullptr, false);
		}
	}
}

void UItemStackSlotWidget::OnClick()
{
	const FItemStack CurrentItemStack = GetItemDetails();
	UDebugHelpers::ScreenLogInfo("Clicked item stack slot widget ("+CurrentItemStack.ItemId+", "+FString::FromInt(CurrentItemStack.Quantity)+")");
}

FItemStack UItemStackSlotWidget::GetItemDetails() const
{
	if(!InventoryAC.GetObject())
	{
		UDebugHelpers::ScreenLogWarning("Inventory does not exist.");
		return FItemStack::Null();
	}
	
	FItemStack Stack = IInventoryInterface::Execute_GetItemStackAtIndex(
		InventoryAC.GetObject(),
		InventoryACIndex);
	return Stack;
}
