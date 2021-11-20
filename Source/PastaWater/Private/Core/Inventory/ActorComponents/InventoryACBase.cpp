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
	DOREPLIFETIME(UInventoryACBase, ItemStacks);
}

void UInventoryACBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryACBase::Init(const int Size)
{
	this->MaxInventorySize = Size;
	this->ItemStacks.Init(FItemStack::Null(), Size);
}

void UInventoryACBase::OnRep_MaxInventorySize()
{
}

void UInventoryACBase::OnRep_ItemStacks()
{
	UpdateInventoryDelegate.Broadcast(ItemStacks);
}

FItemStack UInventoryACBase::GetItemStackAtIndex_Implementation(const int Index) const
{
	if(this->ItemStacks.IsValidIndex(Index))
	{
		return this->ItemStacks[Index];
	}
	return FItemStack::Null();
}

void UInventoryACBase::SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack)
{
	if(!this->ItemStacks.IsValidIndex(Index))
	{
		return;
	}
	
	const FItemStack NewItemStack = ItemStack;
	this->ItemStacks[Index] = NewItemStack;
	UpdateItemSlot(Index);
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
		FItemStack CurrentItemStack = ItemStacks[i];
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
		FItemStack CurrentItemStack = ItemStacks[i];
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
				ItemStacks[i] = CurrentItemStack;
				UpdateItemSlot(i);
				return FItemStack::Null();
			} else
			{
				CurrentItemStack = FItemStack(CurrentItemStack.ItemId, CurrentItemStack.Quantity - QuantityToAdd); // Scrape off overflow
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
		const FItemStack CurrentItemStack = ItemStacks[i];
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
		FItemStack CurrentItemStack = ItemStacks[i];
		int CurrentQuantity = CurrentItemStack.Quantity;
		if(CurrentItemStack.ItemId == ItemStack.ItemId)
		{
			// Try to remove from slot
			CurrentQuantity -= QuantityToRemove;
			QuantityToRemove = -CurrentItemStack.Quantity;
			if(QuantityToRemove <= 0)
			{
				UpdateItemSlot(i);
				return FItemStack::Null();
			}
			ItemStacks[i] = FItemStack(CurrentItemStack.ItemId, CurrentQuantity);
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

TArray<FItemStack> UInventoryACBase::GetAllItemStacks_Implementation() const
{
	return ItemStacks;
}

TArray<FItemStack> UInventoryACBase::RemoveAllItemStacks_Implementation()
{
	TArray<FItemStack> ItemStacksCopy = ItemStacks;
	for(int i = 0; i < MaxInventorySize; i++) // Set all stacks to null
	{
		ItemStacks[i] = FItemStack::Null();
		UpdateItemSlot(i);
	}
	return ItemStacksCopy;
}

void UInventoryACBase::UpdateItemSlot(const int Index)
{
	// If item has a quantity of zero, slot should now be nullptr.
	const FItemStack ItemStack = Execute_GetItemStackAtIndex(this, Index);
	if(ItemStack.Quantity <= 0)
	{
		ItemStacks[Index] = FItemStack::Null();
	}
	UpdateInventoryDelegate.Broadcast(ItemStacks);
}

FItem* UInventoryACBase::FindItem(const FString ItemId) const
{
	const APastaWaterGameState* PastaWaterGameState = APastaWaterGameState::GetGameState(this);
	if(!IsValid(PastaWaterGameState)){return nullptr;}
	return PastaWaterGameState->FindItem(ItemId);
}