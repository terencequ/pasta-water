// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/Actors/ItemInteractable.h"


AItemInteractable::AItemInteractable()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AItemInteractable::OnInteract_Implementation(const TScriptInterface<IInteractorInterface>& InteractorInterface)
{
	Super::OnInteract_Implementation(InteractorInterface);
}

