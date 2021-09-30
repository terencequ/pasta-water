#include "Player/PlayerInventoryAC.h"
#include "Core/Inventory/Models/ItemStackContainerBase.h"

UPlayerInventoryAC::UPlayerInventoryAC() : UInventoryACBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInventoryAC::BeginPlay()
{
	Super::BeginPlay();

	// Initialize inventory
	Inventory = UItemStackContainerBase::Make(50);
}