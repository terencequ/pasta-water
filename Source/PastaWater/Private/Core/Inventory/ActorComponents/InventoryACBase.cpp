// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/ActorComponents/InventoryACBase.h"

#include "Core/Game/PastaWaterGameState.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Net/UnrealNetwork.h"

UInventoryACBase::UInventoryACBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UInventoryACBase::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryACBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInventoryACBase, MaxInventorySize);
	DOREPLIFETIME(UInventoryACBase, InventoryItemStacks);
}

void UInventoryACBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryACBase::Init(const int InventorySize)
{
	this->MaxInventorySize = InventorySize;
	this->InventoryItemStacks.Init(FItemStack::Null(), InventorySize);
}

void UInventoryACBase::OnRep_MaxInventorySize()
{
}

void UInventoryACBase::OnRep_InventoryItemStacks()
{
	UpdateInventoryDelegate.Broadcast(Execute_GetAllItemStacks(this));
}

FItemStack UInventoryACBase::GetItemStackAtIndex_Implementation(const int Index) const
{
	if(this->InventoryItemStacks.IsValidIndex(Index))
	{
		return this->InventoryItemStacks[Index];
	}
	
	UDebugHelpers::ScreenLogError("Tried to get an item stack that was out of range. Index: "+FString::FromInt(Index));
	return FItemStack::Null();
}

void UInventoryACBase::SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack)
{
	// If item has a quantity of zero, slot should now be nullptr.
	FItemStack NewItemStack = ItemStack;
	if(ItemStack.Quantity <= 0)
	{
		NewItemStack = FItemStack::Null();
	}
	
	if(InventoryItemStacks.IsValidIndex(Index))
	{
		InventoryItemStacks[Index] = NewItemStack;
		UpdateInventoryDelegate.Broadcast(Execute_GetAllItemStacks(this));
		return;
	}
	
	UDebugHelpers::ScreenLogError("Tried to set an item stack that was out of range. Index: "+FString::FromInt(Index));
}

int UInventoryACBase::GetContainerSize_Implementation() const
{
	return this->MaxInventorySize;
}

void UInventoryACBase::SwapItemStacks_Implementation(const int FirstIndex, const int SecondIndex)
{
	const FItemStack TempItemStack = Execute_GetItemStackAtIndex(this, FirstIndex);
	Execute_SetItemStackAtIndex(this, FirstIndex, Execute_GetItemStackAtIndex(this, SecondIndex));
	Execute_SetItemStackAtIndex(this, SecondIndex, TempItemStack);
}

bool UInventoryACBase::CanInsertItemStack_Implementation(const FItemStack ItemStack) const
{
	// Negative/zero quantity check
	const FItem* Item = FindItem(ItemStack.ItemId);
	if(Item == nullptr)
	{
		return false;
	}
	
	if(ItemStack.Quantity <= 0)
	{
		return true;
	}

	// Loop through and count up available space
	int FreeSpaceForItem = 0;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack CurrentItemStack = InventoryItemStacks[i];
		if(CurrentItemStack.IsNull())
		{
			FreeSpaceForItem += Item->MaxStackQuantity;
		} else if(CurrentItemStack.ItemId == ItemStack.ItemId)
		{
			FreeSpaceForItem += Item->MaxStackQuantity - CurrentItemStack.Quantity;
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

FItemStack UInventoryACBase::InsertItemStack_Implementation(const FItemStack ItemStack)
{
	// Negative/zero quantity check
	const FItem* Item = FindItem(ItemStack.ItemId);
	if(Item == nullptr)
	{
		return FItemStack::Null();
	}
	
 	if(ItemStack.Quantity <= 0)
	{
		return FItemStack::Null();
	}

	UDebugHelpers::ScreenLogInfo("Inserting "+Item->Name+" (id: "+ItemStack.ItemId+") of quantity "+FString::FromInt(ItemStack.Quantity));
	
	// Loop item stack insertion
	int QuantityToAdd = ItemStack.Quantity;
	for(int i = 0; i < MaxInventorySize; i++)
	{
		FItemStack CurrentItemStack = Execute_GetItemStackAtIndex(this, i);
		if(CurrentItemStack.IsNull())
		{
			CurrentItemStack = FItemStack(ItemStack.ItemId, CurrentItemStack.Quantity);
		} 
		if(CurrentItemStack.ItemId == ItemStack.ItemId)
		{
			// Try to insert into slot, scrape off the overflow and set TempItemStack quantity to overflow
			CurrentItemStack = FItemStack(CurrentItemStack.ItemId, CurrentItemStack.Quantity + QuantityToAdd);
			QuantityToAdd = CurrentItemStack.Quantity - Item->MaxStackQuantity;
			if(QuantityToAdd <= 0)
			{
				Execute_SetItemStackAtIndex(this, i, CurrentItemStack);
				return FItemStack::Null();
			} else
			{
				CurrentItemStack = FItemStack(CurrentItemStack.ItemId, CurrentItemStack.Quantity - QuantityToAdd); // Scrape off overflow
				Execute_SetItemStackAtIndex(this, i, CurrentItemStack);
			}
		}
	}

	// Negative/zero quantity check
	if(QuantityToAdd <= 0)
	{
		return FItemStack::Null();
	}

	// Create stack containing overflow quantity
	const FItemStack OverflowItemStack = FItemStack(ItemStack.ItemId, QuantityToAdd);
	UDebugHelpers::ScreenLogInfo("An overload of "+Item->Name+" (id: "+OverflowItemStack.ItemId+") has been made of quantity "+FString::FromInt(OverflowItemStack.Quantity));
	return OverflowItemStack;
}

bool UInventoryACBase::CanRemoveItemStack_Implementation(const FItemStack ItemStack) const
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
		const FItemStack CurrentItemStack = InventoryItemStacks[i];
		if(CurrentItemStack.ItemId == ItemStack.ItemId)
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

FItemStack UInventoryACBase::RemoveItemStack_Implementation(const FItemStack ItemStack)
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
		FItemStack CurrentItemStack = InventoryItemStacks[i];
		int CurrentQuantity = CurrentItemStack.Quantity;
		if(CurrentItemStack.ItemId == ItemStack.ItemId)
		{
			// Try to remove from slot
			CurrentQuantity -= QuantityToRemove;
			QuantityToRemove = -CurrentItemStack.Quantity;
			if(QuantityToRemove <= 0)
			{
				return FItemStack::Null();
			}
			CurrentItemStack = FItemStack(CurrentItemStack.ItemId, CurrentQuantity);
			Execute_SetItemStackAtIndex(this, i, CurrentItemStack);
		}
	}

	// Negative/zero quantity check
	if(QuantityToRemove <= 0)
	{
		return FItemStack::Null();
	}

	// Create stack containing overflow quantity
	FItemStack OverflowItemStack = FItemStack(ItemStack.ItemId, QuantityToRemove); 
	return OverflowItemStack;
}

TArray<FItemStack> UInventoryACBase::GetAllItemStacks_Implementation() const
{
	return InventoryItemStacks;
}

TArray<FItemStack> UInventoryACBase::RemoveAllItemStacks_Implementation()
{
	TArray<FItemStack> ItemStacksCopy = InventoryItemStacks;
	for(int i = 0; i < MaxInventorySize; i++) // Set all stacks to null
	{
		Execute_SetItemStackAtIndex(this, i, FItemStack::Null());
	}
	return ItemStacksCopy;
}

FItem* UInventoryACBase::FindItem(const FString ItemId) const
{
	const APastaWaterGameState* PastaWaterGameState = APastaWaterGameState::GetGameState(this);
	if(!IsValid(PastaWaterGameState)){return nullptr;}
	return PastaWaterGameState->FindItem(ItemId);
}