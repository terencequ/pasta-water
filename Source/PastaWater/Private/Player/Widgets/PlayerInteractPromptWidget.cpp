// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Widgets/PlayerInteractPromptWidget.h"

#include "Core/Helpers/DebugHelpers.h"
#include "Core/Interact/Interfaces/InteractableInterface.h"

UPlayerInteractPromptWidget* UPlayerInteractPromptWidget::Create(TSubclassOf<UPlayerInteractPromptWidget> UInteractPromptWidgetClass,
                                                     APlayerController* OwningPlayerController, UPlayerInteractorAC* OwningPlayerInteractor)
{
	// Create widget
	UPlayerInteractPromptWidget* InteractPromptWidget = CreateWidget<UPlayerInteractPromptWidget>(
		OwningPlayerController,
		UInteractPromptWidgetClass,
		"Interact Prompt");

	// Failure check
	if(!IsValid(InteractPromptWidget))
	{
		UDebugHelpers::ScreenLogError("Could not initialise Interact Prompt Widget.");
		return nullptr;
	}

	// Setup widget and return
	UDebugHelpers::ScreenLogInfo("Initialised Interact Prompt Widget.");

	InteractPromptWidget->Setup(OwningPlayerInteractor);
	InteractPromptWidget->SetVisibility(ESlateVisibility::Hidden);
	InteractPromptWidget->AddToViewport();
	return InteractPromptWidget;
}

bool UPlayerInteractPromptWidget::Setup(UPlayerInteractorAC* OwningPlayerInteractorAC)
{
	// Get dependent variables
	PlayerController = Cast<APastaWaterPlayerControllerBase>(GetOwningPlayer());
	if(!IsValid(PlayerController))
		return false;
	
	InteractorAC = OwningPlayerInteractorAC;
	if(!IsValid(InteractorAC))
		return false;

	InteractorAC->UpdateInteractablesDelegate.AddUObject(this, &UPlayerInteractPromptWidget::OnUpdateInteractables);
	return true;
}

void UPlayerInteractPromptWidget::OnUpdateInteractables(TArray<TScriptInterface<IInteractableInterface>> Interactables)
{
	if(IsValid(Interactables[0].GetObject()))
	{
		SetVisibility(ESlateVisibility::Visible);
	} else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

