// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Interact/Interfaces/InteractorInterface.h"
#include "Player/PlayerInteractorAC.h"
#include "PlayerInteractPromptWidget.generated.h"

/**
 * Widget that displays a prompt for user interaction.
 */
UCLASS()
class PASTAWATER_API UPlayerInteractPromptWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	APastaWaterPlayerControllerBase* PlayerController;
	
	UPROPERTY(BlueprintReadWrite)
	UInteractorACBase* InteractorAC;

	UFUNCTION(BlueprintCallable)
	static UPlayerInteractPromptWidget* Create(
		TSubclassOf<UPlayerInteractPromptWidget> UInteractPromptWidgetClass,
		APlayerController* OwningPlayerController,
		UPlayerInteractorAC* InteractorInterface);

	UFUNCTION(BlueprintCallable)
	bool Setup(UPlayerInteractorAC* OwningPlayerInteractorAC);

	/**
	 * Delegate callback method, for when interactables list gets updated.
	 */
	UFUNCTION(BlueprintCallable)
	void OnUpdateInteractables(TArray<TScriptInterface<IInteractableInterface>> Interactables);
};
