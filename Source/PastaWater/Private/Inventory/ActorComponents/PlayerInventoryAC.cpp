// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ActorComponents/PlayerInventoryAC.h"


// Sets default values for this component's properties
UPlayerInventoryAC::UPlayerInventoryAC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPlayerInventoryAC::BeginPlay()
{
	Super::BeginPlay();

	// Initialize inventory
	Inventory = UItemStackContainerBase::Make(50);
}


// Called every frame
void UPlayerInventoryAC::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FItemStack UPlayerInventoryAC::GetItemStackAtIndex_Implementation(const int Index) const
{
	return IItemStackContainerInterface::Execute_GetItemStackAtIndex(Inventory.GetObject(), Index);
}

void UPlayerInventoryAC::SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack)
{
	return IItemStackContainerInterface::Execute_SetItemStackAtIndex(Inventory.GetObject(), Index, ItemStack);
}

void UPlayerInventoryAC::SwapItemStacks_Implementation(const int FirstIndex, const int SecondIndex)
{
	return IItemStackContainerInterface::Execute_SwapItemStacks(Inventory.GetObject(), FirstIndex, SecondIndex);
}

bool UPlayerInventoryAC::CanInsertItemStack_Implementation(const FItemStack ItemStack) const
{
	return IItemStackContainerInterface::Execute_CanInsertItemStack(Inventory.GetObject(), ItemStack);
}

FItemStack UPlayerInventoryAC::InsertItemStack_Implementation(const FItemStack ItemStack)
{
	return IItemStackContainerInterface::Execute_InsertItemStack(Inventory.GetObject(), ItemStack);
}

bool UPlayerInventoryAC::CanRemoveItemStack_Implementation(const FItemStack ItemStack) const
{
	return IItemStackContainerInterface::Execute_CanRemoveItemStack(Inventory.GetObject(), ItemStack);
}

FItemStack UPlayerInventoryAC::RemoveItemStack_Implementation(const FItemStack ItemStack)
{
	return IItemStackContainerInterface::Execute_RemoveItemStack(Inventory.GetObject(), ItemStack);
}

TArray<FItemStack> UPlayerInventoryAC::GetAllItemStacks_Implementation() const
{
	return IItemStackContainerInterface::Execute_GetAllItemStacks(Inventory.GetObject());
}

TArray<FItemStack> UPlayerInventoryAC::RemoveAllItemStacks_Implementation()
{
	return IItemStackContainerInterface::Execute_RemoveAllItemStacks(Inventory.GetObject());
}