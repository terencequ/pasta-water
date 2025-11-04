#include "Player/PlayerInventoryAC.h"

#include "Core/Helpers/DebugHelpers.h"
#include "Net/UnrealNetwork.h"

UPlayerInventoryAC::UPlayerInventoryAC() : UInventoryACBase()
{
}

void UPlayerInventoryAC::BeginPlay()
{
	Super::BeginPlay();
	Init(10, 50);
}

void UPlayerInventoryAC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UPlayerInventoryAC, HotbarItemStacks);
	DOREPLIFETIME(UPlayerInventoryAC, MouseItemStack);
	DOREPLIFETIME(UPlayerInventoryAC, CurrentSelectedHotbarIndex);
}

void UPlayerInventoryAC::Init(int HotbarSize, int InventorySize)
{
	this->MaxHotbarSize = HotbarSize;
	this->HotbarItemStacks.Init(FItemStack::Null(), HotbarSize);
	Super::Init(InventorySize);
}

void UPlayerInventoryAC::OnRep_MaxHotbarSize()
{
}

void UPlayerInventoryAC::OnRep_HotbarItemStacks() const
{
	UpdateInventoryDelegate.Broadcast(Execute_GetAllItemStacks(this));
}

void UPlayerInventoryAC::OnRep_MouseItemStack() const
{
	UpdateInventoryDelegate.Broadcast(Execute_GetAllItemStacks(this));
}

void UPlayerInventoryAC::OnRep_CurrentSelectedHotbarIndex() const
{
}

FItemStack UPlayerInventoryAC::GetItemStackAtIndex_Implementation(const int Index) const
{
	// Mouse slot
	if(Index == -1)
	{
		return MouseItemStack;
	}
	// Hotbar
	else if(Index >= 0 && Index < MaxHotbarSize)
	{
		const int NewIndex = Index;
		if(HotbarItemStacks.IsValidIndex(NewIndex))
		{
			return HotbarItemStacks[NewIndex];
		}
	}
	// Inventory
	else 
	{
		const int NewIndex = Index - MaxHotbarSize;
		if(InventoryItemStacks.IsValidIndex(NewIndex))
		{
			return InventoryItemStacks[NewIndex];
		}
	}

	UDebugHelpers::ScreenLogError("Tried to get an item stack that was out of range. Index: "+FString::FromInt(Index));
	return FItemStack::Null();
}

void UPlayerInventoryAC::SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack)
{
	// If item has a quantity of zero, slot should now be nullptr.
	FItemStack NewItemStack = ItemStack;
	if(ItemStack.Quantity <= 0)
	{
		NewItemStack = FItemStack::Null();
	}
	
	// Mouse slot
	if(Index == -1)
	{
		MouseItemStack = NewItemStack;
		UpdateInventoryDelegate.Broadcast(Execute_GetAllItemStacks(this));
		return;
	}
	// Hotbar
	else if(Index >= 0 && Index < MaxHotbarSize)
	{
		const int NewIndex = Index;
		if(HotbarItemStacks.IsValidIndex(NewIndex))
		{
			HotbarItemStacks[NewIndex] = NewItemStack;
			UpdateInventoryDelegate.Broadcast(Execute_GetAllItemStacks(this));
			return;
		}
	}
	// Inventory
	else 
	{
		const int NewIndex = Index - MaxHotbarSize;
		if(InventoryItemStacks.IsValidIndex(NewIndex))
		{
			InventoryItemStacks[NewIndex] = NewItemStack;
			UpdateInventoryDelegate.Broadcast(Execute_GetAllItemStacks(this));
			return;
		}
	}
	
	UDebugHelpers::ScreenLogError("Tried to set an item stack that was out of range. Index: "+FString::FromInt(Index));
}

int UPlayerInventoryAC::GetContainerSize_Implementation() const
{
	return MaxInventorySize + MaxHotbarSize; // Inventory + Hotbar
}

void UPlayerInventoryAC::SelectNextHotbarIndex()
{
	CurrentSelectedHotbarIndex = (CurrentSelectedHotbarIndex - 1 + MaxHotbarSize) % MaxHotbarSize;
	UpdateHotbarSelectionDelegate.Broadcast(CurrentSelectedHotbarIndex);
}

void UPlayerInventoryAC::SelectPreviousHotbarIndex()
{
	CurrentSelectedHotbarIndex = (CurrentSelectedHotbarIndex + 1) % MaxHotbarSize;
	UpdateHotbarSelectionDelegate.Broadcast(CurrentSelectedHotbarIndex);
}

FItemStack UPlayerInventoryAC::GetItemStackAtSelectedHotbarIndex() const
{
	return HotbarItemStacks[CurrentSelectedHotbarIndex];
}

int UPlayerInventoryAC::GetCurrentSelectedHotbarIndex() const
{
	return CurrentSelectedHotbarIndex;
}
