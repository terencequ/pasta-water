// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/ActorComponents/PlayerInventoryDisplayAC.h"

#include "PastaWaterPlayerControllerBase.h"
#include "Helpers/DebugHelpers.h"

UPlayerInventoryDisplayAC::UPlayerInventoryDisplayAC()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInventoryDisplayAC::BeginPlay()
{
	Super::BeginPlay();

	// Setup dependent variables.
	PlayerController = APastaWaterPlayerControllerBase::CastFromActor(GetOwner());
	if(!IsValid(PlayerController))
		return;
	PlayerInventoryAC = PlayerController->GetInventoryACOrDefault();
	
	// Setup widget
	PlayerInventoryWidget = CreateWidget<UPlayerInventoryWidget>(PlayerController, PlayerInventoryWidgetClass, "Player Inventory");
	if(IsValid(PlayerInventoryWidget))
	{
		PlayerInventoryWidget->Initialise();
		PlayerInventoryWidget->CreateInventorySlots();
		PlayerInventoryWidget->UpdateInventorySlots();
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		PlayerInventoryWidget->AddToViewport();
	}
}

void UPlayerInventoryDisplayAC::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPlayerInventoryDisplayAC::ToggleInventory()
{
	PlayerInventoryWidget->UpdateInventorySlots();
	if(!IsValid(PlayerInventoryWidget))
	{
		UDebugHelpers::ScreenLogError("Player Inventory Widget was not set up properly!");
		return;
	}
	if(!IsValid(PlayerController))
	{
		UDebugHelpers::ScreenLogError("Player Controller was not set up properly!");
		return;
	}

	if(PlayerInventoryWidget->IsVisible())
	{
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		PlayerController->FlushInputs();
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->EnableAllInputs();
		PlayerController->SetShowMouseCursor(false);
		UDebugHelpers::ScreenLogInfo("Player Inventory UI hidden.");
	} else
	{
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		PlayerController->FlushInputs();
		PlayerController->DisableAllInputs();

		// Input mode
		FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		InputMode.SetWidgetToFocus(PlayerInventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		InputMode.SetHideCursorDuringCapture(false);
		PlayerController->SetInputMode(InputMode);
		
		PlayerController->SetShowMouseCursor(true);
		UDebugHelpers::ScreenLogInfo("Player Inventory UI showed.");
	}
}



