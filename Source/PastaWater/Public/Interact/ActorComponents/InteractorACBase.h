// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interact/Interfaces/InteractableInterface.h"
#include "Interact/Interfaces/InteractorInterface.h"
#include "InteractorACBase.generated.h"

UCLASS(Blueprintable)
class PASTAWATER_API UInteractorACBase : public UActorComponent, public IInteractorInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractorACBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact_Implementation(const TScriptInterface<IInteractableInterface>& Interactable) override;
};
