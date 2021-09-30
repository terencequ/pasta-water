// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PastaWaterPlayerController.h"

#include "Core/Helpers/DebugHelpers.h"

class UPlayerInteractorAC;

APastaWaterPlayerController::APastaWaterPlayerController() : APastaWaterPlayerControllerBase()
{
}

void APastaWaterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Actor component registration
	PlayerInventoryAC = CreateDefaultSubobject<UPlayerInventoryAC>(TEXT("Player Inventory"));
	AddOwnedComponent(PlayerInventoryAC);

	PlayerInteractorAC = CreateDefaultSubobject<UPlayerInteractorAC>(TEXT("Player Interactor"));
	AddOwnedComponent(PlayerInteractorAC);
	
	InitialiseInventory();
}

void APastaWaterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Input binds
	if(InputComponent)
	{
		InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &APastaWaterPlayerController::PerformToggleInventoryAction);
		InputComponent->BindAction("Primary", IE_Pressed, this, &APastaWaterPlayerController::PerformPrimaryAction);
	}
}

void APastaWaterPlayerController::OnPossess(APawn* MovieSceneBlends)
{
	Super::OnPossess(MovieSceneBlends);
}

void APastaWaterPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

// Inputs
void APastaWaterPlayerController::PerformToggleInventoryAction()
{
	ToggleInventory();
}

void APastaWaterPlayerController::PerformPrimaryAction()
{
	if(!PrimaryActionEnabled) { return; }
	IInteractorInterface::Execute_Interact(PlayerInteractorAC, nullptr);
}

void APastaWaterPlayerController::EnableAllInputs()
{
	Super::EnableAllInputs();
	PrimaryActionEnabled = true;
}

void APastaWaterPlayerController::DisableAllInputs()
{
	Super::DisableAllInputs();
	PrimaryActionEnabled = false;
}

// Inventory
void APastaWaterPlayerController::InitialiseInventory()
{
	PlayerInventoryWidget = UPlayerInventoryWidget::Create(PlayerInventoryWidgetClass, this, PlayerInventoryAC);
}

void APastaWaterPlayerController::ToggleInventory()
{
	if(!IsValid(PlayerInventoryWidget))
	{
		UDebugHelpers::ScreenLogError("Player Inventory Widget was not set up properly!");
		return;
	}
	
	PlayerInventoryWidget->UpdateInventorySlots();
	ToggleWidgetFocus(PlayerInventoryWidget);
}