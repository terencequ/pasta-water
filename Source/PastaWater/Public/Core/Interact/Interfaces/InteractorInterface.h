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
	/**
	 * Get all valid interactables that can be interacted with. This should be implemented to get a list of one or more
	 * interactables that the implementation to interact with. i.e. Interactables in a 5m radius.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction Stats")
	TArray<TScriptInterface<IInteractableInterface>> GetValidInteractables() const;

	/**
	 * Interact. This should be implemented to affect all interactables in the Valid Interactables list.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction Action")
	void Interact();
};
