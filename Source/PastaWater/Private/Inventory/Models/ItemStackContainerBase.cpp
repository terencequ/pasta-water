#include "Inventory/Models/ItemStackContainerBase.h"

#include <string>

#include "Helpers/DebugHelpers.h"

void UItemStackContainerBase::Init(const int Size)
{
	this->MaxInventorySize = Size;
	this->ItemStacks.Init(FItemStack::Null(), Size);
}

FItemStack UItemStackContainerBase::GetItemStackAtIndex_Implementation(const int Index) const
{
	if(this->ItemStacks.IsValidIndex(Index))
	{
		return this->ItemStacks[Index];
	}
	return FItemStack::Null();
}

void UItemStackContainerBase::SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack)
{
	if(this->ItemStacks.IsValidIndex(Index))
	{
		const FItemStack NewItemStack = ItemStack;
		this->ItemStacks[Index] = NewItemStack;
		UpdateItemSlot(Index);
	}
	// Else, do nothing.
}

int UItemStackContainerBase::GetContainerSize_Implementation() const
{
	return this->MaxInventorySize;
}

void UItemStackContainerBase::SwapItemStacks_Implementation(const int FirstIndex, const int SecondIndex)
{
	const FItemStack TempItemStack = Execute_GetItemStackAtIndex(this, FirstIndex);
	Execute_SetItemStackAtIndex(this, FirstIndex, Execute_GetItemStackAtIndex(this, SecondIndex));
	Execute_SetItemStackAtIndex(this, SecondIndex, TempItemStack);
}

bool UItemStackContainerBase::CanInsertItemStack_Implementation(const FItemStack ItemStack) const
{
	// Negative/zero quantity check
	if(ItemStack.Quantity <= 0)
	{
		return true;
	}

	// Loop through and count up available space
	int FreeSpaceForItem = 0;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack CurrentItemStack = ItemStacks[i];
		if(CurrentItemStack.IsNull())
		{
			FreeSpaceForItem += ItemStack.Item.MaxStackQuantity;
		} else if(CurrentItemStack.Item.Id == ItemStack.Item.Id)
		{
			FreeSpaceForItem += CurrentItemStack.Item.MaxStackQuantity - CurrentItemStack.Quantity;
		}

		if(FreeSpaceForItem >= ItemStack.Quantity)
		{
			// At this point we know that there is enough room for whole stack
			return true;
		}
	}

	// Hasn't returned yet. There isn't any room for the stack.
	return false;
}

FItemStack UItemStackContainerBase::InsertItemStack_Implementation(const FItemStack ItemStack)
{
	// Negative/zero quantity check
 	if(ItemStack.Quantity <= 0)
	{
		return FItemStack::Null();
	}

	// Loop item stack insertion
	int QuantityToAdd = ItemStack.Quantity;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack CurrentItemStack = ItemStacks[i];
		if(CurrentItemStack.IsNull())
		{
			CurrentItemStack = FItemStack(ItemStack.Item, CurrentItemStack.Quantity);
		} 
		if(CurrentItemStack.Item.Id == ItemStack.Item.Id)
		{
			// Try to insert into slot, scrape off the overflow and set TempItemStack quantity to overflow
			CurrentItemStack = FItemStack(CurrentItemStack.Item, CurrentItemStack.Quantity + QuantityToAdd);
			QuantityToAdd = CurrentItemStack.Quantity - CurrentItemStack.Item.MaxStackQuantity;
			if(QuantityToAdd <= 0)
			{
				ItemStacks[i] = CurrentItemStack;
				UpdateItemSlot(i);
				return FItemStack::Null();
			} else
			{
				CurrentItemStack = FItemStack(CurrentItemStack.Item, CurrentItemStack.Quantity - QuantityToAdd); // Scrape off overflow
				ItemStacks[i] = CurrentItemStack;
				UpdateItemSlot(i);
			}
		}
	}

	// Negative/zero quantity check
	if(QuantityToAdd <= 0)
	{
		return FItemStack::Null();
	}

	// Create stack containing overflow quantity
	FItemStack OverflowItemStack = FItemStack(ItemStack.Item, QuantityToAdd);
	UDebugHelpers::ScreenLogInfo("An overload of "+OverflowItemStack.Item.Name+" (id: "+OverflowItemStack.Item.Id+") has been made of quantity "+FString::FromInt(OverflowItemStack.Quantity)+"");
	return OverflowItemStack;
}

bool UItemStackContainerBase::CanRemoveItemStack_Implementation(const FItemStack ItemStack) const
{
	// Negative/zero quantity check
	if(ItemStack.Quantity <= 0)
	{
		return true;
	}

	// Count all items of same type
	int Quantity = 0;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack CurrentItemStack = ItemStacks[i];
		if(CurrentItemStack.Item.Id == ItemStack.Item.Id)
		{
			Quantity += CurrentItemStack.Quantity;
			if(Quantity >= ItemStack.Quantity)
			{
				// We know at this point that enough items of this type exist in the inventory.
				return true;
			}
		}
	}
	return false;
}

FItemStack UItemStackContainerBase::RemoveItemStack_Implementation(const FItemStack ItemStack)
{
	// Negative/zero quantity check
	if(ItemStack.Quantity <= 0)
	{
		return FItemStack::Null();
	}

	// Loop item stack insertion
	int QuantityToRemove = ItemStack.Quantity;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack CurrentItemStack = ItemStacks[i];
		if(CurrentItemStack.Item.Id == ItemStack.Item.Id)
		{
			// Try to remove from slot
			CurrentItemStack.Quantity -= QuantityToRemove;
			QuantityToRemove = -CurrentItemStack.Quantity;
			if(QuantityToRemove <= 0)
			{
				UpdateItemSlot(i);
				return FItemStack::Null();
			}
			CurrentItemStack.Quantity = 0; // Normalize item stack quantity, since it is negative
			UpdateItemSlot(i);
		}
	}

	// Negative/zero quantity check
	if(QuantityToRemove <= 0)
	{
		return FItemStack::Null();
	}

	// Create stack containing overflow quantity
	FItemStack OverflowItemStack = ItemStack; 
	OverflowItemStack.Quantity = QuantityToRemove;
	return OverflowItemStack;
}

TArray<FItemStack> UItemStackContainerBase::GetAllItemStacks_Implementation() const
{
	return ItemStacks;
}

TArray<FItemStack> UItemStackContainerBase::RemoveAllItemStacks_Implementation()
{
	TArray<FItemStack> ItemStacksCopy = ItemStacks;
	for(int i = 0; i < MaxInventorySize; i++) // Set all stacks to null
	{
		ItemStacks[i] = FItemStack::Null(); 
	}
	return ItemStacksCopy;
}

void UItemStackContainerBase::UpdateItemSlot(const int Index)
{
	// If item has a quantity of zero, slot should now be nullptr.
	const FItemStack ItemStack = Execute_GetItemStackAtIndex(this, Index);
	if(ItemStack.Quantity == 0)
	{
		ItemStacks[Index] = FItemStack::Null();
	}
}

UItemStackContainerBase* UItemStackContainerBase::Make(const int MaxInventorySize)
{
	UItemStackContainerBase* NewContainer = NewObject<UItemStackContainerBase>();
	NewContainer->Init(MaxInventorySize);
	return NewContainer;
}

