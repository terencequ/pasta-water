// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Widgets/InteractPromptWidget.h"

#include "Core/Helpers/DebugHelpers.h"
#include "Core/Interact/Interfaces/InteractableInterface.h"

UInteractPromptWidget* UInteractPromptWidget::Create(TSubclassOf<UInteractPromptWidget> UInteractPromptWidgetClass,
                                                     APlayerController* OwningPlayerController, UPlayerInteractorAC* OwningPlayerInteractor)
{
	// Create widget
	UInteractPromptWidget* InteractPromptWidget = CreateWidget<UInteractPromptWidget>(
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

bool UInteractPromptWidget::Setup(UPlayerInteractorAC* OwningPlayerInteractor)
{
	// Get dependent variables
	PlayerController = Cast<APastaWaterPlayerControllerBase>(GetOwningPlayer());
	if(!IsValid(PlayerController))
		return false;
	
	Interactor = OwningPlayerInteractor;
	if(!IsValid(Interactor))
		return false;

	Interactor->UpdateInteractablesDelegate.AddUObject(this, &UInteractPromptWidget::OnUpdateInteractables);
	return true;
}

void UInteractPromptWidget::OnUpdateInteractables(TArray<TScriptInterface<IInteractableInterface>> Interactables)
{
	if(IsValid(Interactables[0].GetObject()))
	{
		SetVisibility(ESlateVisibility::Visible);
	} else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

