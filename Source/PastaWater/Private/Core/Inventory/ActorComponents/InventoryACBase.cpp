// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Inventory/ActorComponents/InventoryACBase.h"
#include "Core/Inventory/Models/ItemStackContainerBase.h"

UInventoryACBase::UInventoryACBase()
{
}

void UInventoryACBase::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryACBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

FItemStack UInventoryACBase::GetItemStackAtIndex_Implementation(const int Index) const
{
	return IItemStackContainerInterface::Execute_GetItemStackAtIndex(Inventory.GetObject(), Index);
}

void UInventoryACBase::SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack)
{
	return IItemStackContainerInterface::Execute_SetItemStackAtIndex(Inventory.GetObject(), Index, ItemStack);
}

int UInventoryACBase::GetContainerSize_Implementation() const
{
	return IItemStackContainerInterface::Execute_GetContainerSize(Inventory.GetObject());
}

void UInventoryACBase::SwapItemStacks_Implementation(const int FirstIndex, const int SecondIndex)
{
	return IItemStackContainerInterface::Execute_SwapItemStacks(Inventory.GetObject(), FirstIndex, SecondIndex);
}

bool UInventoryACBase::CanInsertItemStack_Implementation(const FItemStack ItemStack) const
{
	return IItemStackContainerInterface::Execute_CanInsertItemStack(Inventory.GetObject(), ItemStack);
}

FItemStack UInventoryACBase::InsertItemStack_Implementation(const FItemStack ItemStack)
{
	return IItemStackContainerInterface::Execute_InsertItemStack(Inventory.GetObject(), ItemStack);
}

bool UInventoryACBase::CanRemoveItemStack_Implementation(const FItemStack ItemStack) const
{
	return IItemStackContainerInterface::Execute_CanRemoveItemStack(Inventory.GetObject(), ItemStack);
}

FItemStack UInventoryACBase::RemoveItemStack_Implementation(const FItemStack ItemStack)
{
	return IItemStackContainerInterface::Execute_RemoveItemStack(Inventory.GetObject(), ItemStack);
}

TArray<FItemStack> UInventoryACBase::GetAllItemStacks_Implementation() const
{
	return IItemStackContainerInterface::Execute_GetAllItemStacks(Inventory.GetObject());
}

TArray<FItemStack> UInventoryACBase::RemoveAllItemStacks_Implementation()
{
	return IItemStackContainerInterface::Execute_RemoveAllItemStacks(Inventory.GetObject());
}