// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interact/Interfaces/InteractableInterface.h"
#include "GameFramework/Actor.h"
#include "InteractableABase.generated.h"

UCLASS(Blueprintable)
class PASTAWATER_API AInteractableABase : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableABase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract_Implementation(const TScriptInterface<IInteractorInterface>& Interactable) override;
};
