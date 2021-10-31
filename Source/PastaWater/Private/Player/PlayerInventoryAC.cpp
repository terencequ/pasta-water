#include "Player/PlayerInventoryAC.h"

UPlayerInventoryAC::UPlayerInventoryAC() : UInventoryACBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void UPlayerInventoryAC::BeginPlay()
{
	Super::BeginPlay();
	Init(50);
}