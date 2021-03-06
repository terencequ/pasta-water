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
		InitialiseInventoryUI();
		InitialiseInteractPromptUI();
	}
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
	PlayerInventoryWidget = UPlayerInventoryWidget::Create(PlayerInventoryWidgetClass, this, PlayerInventoryAC);
}

void APastaWaterPlayerController::ToggleInventoryUI()
{
	if(!IsValid(PlayerInventoryWidget))
	{
		UDebugHelpers::ScreenLogError("Player Inventory Widget was not set up properly!");
		return;
	}
	
	ToggleWidgetVisibilityAndFocus(PlayerInventoryWidget);
}

// User Interface - Interaction
void APastaWaterPlayerController::InitialiseInteractPromptUI()
{
	if(!IsValid(PlayerInteractorAC)) { return; }
	InteractPromptWidget = UPlayerInteractPromptWidget::Create(InteractPromptWidgetClass, this, PlayerInteractorAC);
}