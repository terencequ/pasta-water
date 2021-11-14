#include "Player/PlayerInventoryAC.h"

UPlayerInventoryAC::UPlayerInventoryAC() : UInventoryACBase()
{
}

void UPlayerInventoryAC::BeginPlay()
{
	Super::BeginPlay();
	Init(50);
}