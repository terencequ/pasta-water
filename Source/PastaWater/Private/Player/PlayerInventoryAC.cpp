#include "Player/PlayerInventoryAC.h"

UPlayerInventoryAC::UPlayerInventoryAC() : UInventoryACBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInventoryAC::BeginPlay()
{
	Super::BeginPlay();
	Init(50);
}