﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/Actors/ItemInteractable.h"

#include "Core/Game/PastaWaterGameState.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Core/Interact/ActorComponents/InteractorACBase.h"
#include "Player/PastaWaterPlayerController.h"


AItemInteractable::AItemInteractable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItemInteractable::OnInteract_Implementation(const TScriptInterface<IInteractorInterface>& InteractorInterface)
{
	Super::OnInteract_Implementation(InteractorInterface);
	if(!IsValid(InteractorInterface.GetObject())){ return; }

	const UActorComponent* ActorComponent = Cast<UActorComponent>(InteractorInterface.GetObject());
	if(!ActorComponent){ return; }

	const APastaWaterPlayerController* PlayerControllerBase = Cast<APastaWaterPlayerController>(ActorComponent->GetOwner());
	if(!IsValid(PlayerControllerBase->PlayerInventoryAC)){ return; }

	const APastaWaterGameState* PastaWaterGameState = APastaWaterGameState::GetGameState(this);
	if(!IsValid(PastaWaterGameState)){return;}
	
	const FItem* Item = PastaWaterGameState->FindItem(ItemId);
	if(Item == nullptr)
	{
		UDebugHelpers::ScreenLogError("Item "+FString::FromInt(ItemId)+" cannot be found.");
	}
	IInventoryInterface::Execute_InsertItemStack(PlayerControllerBase->PlayerInventoryAC, FItemStack(ItemId, 1));
	
}
