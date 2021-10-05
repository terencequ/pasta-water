﻿#include "Core/Interact/ActorComponents/InteractorACBase.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Core/Interact/Interfaces/InteractableInterface.h"

// Sets default values for this component's properties
UInteractorACBase::UInteractorACBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInteractorACBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UInteractorACBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

TArray<TScriptInterface<IInteractableInterface>> UInteractorACBase::GetValidInteractables_Implementation() const
{
	TArray<TScriptInterface<IInteractableInterface>> InteractableInterfaces;
	InteractableInterfaces.Init(TScriptInterface<IInteractableInterface>(nullptr), 0);
	return InteractableInterfaces;
}

void UInteractorACBase::Interact_Implementation(const TScriptInterface<IInteractableInterface>& Interactable)
{
	UDebugHelpers::ScreenLogInfo(GetName()+" interacted with something.");
}
