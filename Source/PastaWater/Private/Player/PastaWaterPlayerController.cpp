#include "Player/PastaWaterPlayerController.h"
#include "Core/Helpers/DebugHelpers.h"

APastaWaterPlayerController::APastaWaterPlayerController() : APastaWaterPlayerControllerBase()
{
	SetReplicates(true);
	bOnlyRelevantToOwner = true;
	
	// Actor component registration
	PlayerInventoryAC = CreateDefaultSubobject<UPlayerInventoryAC>(TEXT("Player Inventory"));
	AddOwnedComponent(PlayerInventoryAC);

	PlayerInteractorAC = CreateDefaultSubobject<UPlayerInteractorAC>(TEXT("Player Interactor"));
	AddOwnedComponent(PlayerInteractorAC);
}

void APastaWaterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocalController())
	{
		// UI initialization
		InitialiseEscapeMenuUI();
		InitialiseInteractPromptUI();
		InitialiseInventoryUI();
	}
}

void APastaWaterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Input binds
	if(InputComponent)
	{
		InputComponent->BindAction("ToggleEscapeMenu", IE_Pressed, this, &APastaWaterPlayerController::PerformToggleEscapeMenuAction);
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
void APastaWaterPlayerController::PerformToggleEscapeMenuAction()
{
	ToggleEscapeMenuUI();
}

void APastaWaterPlayerController::PerformToggleInventoryAction()
{
	ToggleInventoryUI();
}

void APastaWaterPlayerController::PerformPrimaryAction()
{
	if(!PrimaryActionEnabled) { return; }
	UDebugHelpers::ScreenLogInfo("Interacting");
	PlayerInteractorAC->DrawDebugInteractLine();
	IInteractorInterface::Execute_Interact(PlayerInteractorAC);
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

// User Interface - Inventory
void APastaWaterPlayerController::InitialiseInventoryUI()
{
	if(!IsValid(PlayerInventoryAC)) { return; }
	PlayerHotbarWidget = UPlayerHotbarWidget::Create(PlayerHotbarWidgetClass, this, PlayerInventoryAC);
	PlayerInventoryWidget = UPlayerInventoryWidget::Create(PlayerInventoryWidgetClass, this, PlayerInventoryAC);
}

void APastaWaterPlayerController::ToggleEscapeMenuUI()
{
	if (PlayerInventoryWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		UDebugHelpers::ScreenLogInfo("Cannot open Escape Menu while Inventory is open.");
		return;
	}
	
	if(!IsValid(PlayerEscapeMenuWidget))
	{
		UDebugHelpers::ScreenLogError("Player Escape Menu Widget was not set up properly!");
		return;
	}
	ToggleWidgetVisibilityAndFocus(PlayerEscapeMenuWidget);
}

void APastaWaterPlayerController::ToggleInventoryUI()
{
	if (PlayerEscapeMenuWidget->GetVisibility() == ESlateVisibility::Visible)
	{
		UDebugHelpers::ScreenLogInfo("Cannot open Inventory while Escape Menu is open.");
		return;
	}
	
	if(!IsValid(PlayerInventoryWidget))
	{
		UDebugHelpers::ScreenLogError("Player Inventory Widget was not set up properly!");
		return;
	}
	
	ToggleWidgetVisibilityAndFocus(PlayerInventoryWidget);
	
	// Callback for closing inventory
	if(PlayerInventoryWidget->GetVisibility() == ESlateVisibility::Hidden)
	{
		PlayerInventoryWidget->OnCloseInventory();
	}
}

// User Interface - Interaction
void APastaWaterPlayerController::InitialiseInteractPromptUI()
{
	if(!IsValid(PlayerInteractorAC)) { return; }
	InteractPromptWidget = UPlayerInteractPromptWidget::Create(InteractPromptWidgetClass, this, PlayerInteractorAC);
}

// User Interface - Escape Menu
void APastaWaterPlayerController::InitialiseEscapeMenuUI()
{
	PlayerEscapeMenuWidget = UPlayerEscapeMenuWidget::Create(PlayerEscapeMenuWidgetClass, this);
}