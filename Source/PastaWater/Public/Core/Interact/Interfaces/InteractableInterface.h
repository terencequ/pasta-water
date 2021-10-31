// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

class IInteractorInterface;

UINTERFACE()
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for an Interactable. An Interactable is able to be interacted with.
 */
class PASTAWATER_API IInteractableInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	bool Validate_OnInteract(const TScriptInterface<IInteractorInterface>& Interactor);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void Server_OnInteract(const TScriptInterface<IInteractorInterface>& Interactor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interact")
	void NetMulticast_OnInteract(const TScriptInterface<IInteractorInterface>& Interactor);

};
