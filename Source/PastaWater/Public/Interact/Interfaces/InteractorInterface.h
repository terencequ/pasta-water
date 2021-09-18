// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractorInterface.generated.h"

class IInteractableInterface;

UINTERFACE()
class UInteractorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for an Interactor. An Interactor is able to interact with Interactables, to perform an action.
 */
class PASTAWATER_API IInteractorInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void Interact(const TScriptInterface<IInteractableInterface>& Interactable);
};
