// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Interact/Interfaces/InteractorInterface.h"
#include "Player/PlayerInteractorAC.h"
#include "InteractPromptWidget.generated.h"

/**
 * Widget that displays a prompt for user interaction.
 */
UCLASS()
class PASTAWATER_API UInteractPromptWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	APastaWaterPlayerControllerBase* PlayerController;
	
	UPROPERTY(BlueprintReadWrite)
	UInteractorACBase* Interactor;

	UFUNCTION(BlueprintCallable)
	static UInteractPromptWidget* Create(
		TSubclassOf<UInteractPromptWidget> UInteractPromptWidgetClass,
		APlayerController* OwningPlayerController,
		UPlayerInteractorAC* InteractorInterface);

	UFUNCTION(BlueprintCallable)
	bool Setup(UPlayerInteractorAC* OwningPlayerInteractor);

	/**
	 * Delegate callback method, for when interactables list gets updated.
	 */
	UFUNCTION(BlueprintCallable)
	void OnUpdateInteractables(TArray<TScriptInterface<IInteractableInterface>> Interactables);
};
