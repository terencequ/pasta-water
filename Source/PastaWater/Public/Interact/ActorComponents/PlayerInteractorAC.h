// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractorACBase.h"
#include "PlayerInteractorAC.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PASTAWATER_API UPlayerInteractorAC : public UInteractorACBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	APlayerController* PlayerController;
	
	// Sets default values for this component's properties
	UPlayerInteractorAC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact_Implementation(const TScriptInterface<IInteractableInterface>& Interactable) override;
	FVector GetStartVector();
	FVector GetForwardVector();
};
