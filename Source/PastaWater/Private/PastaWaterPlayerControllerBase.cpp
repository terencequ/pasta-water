#include "PastaWaterPlayerControllerBase.h"

#include "PastaWaterCharacterBase.h"
#include "GameFramework/PlayerInput.h"
#include "Helpers/DebugHelpers.h"

APastaWaterPlayerControllerBase::APastaWaterPlayerControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Actor component registration
	PlayerInventoryAC = CreateDefaultSubobject<UPlayerInventoryAC>(TEXT("Player Inventory"));
	AddOwnedComponent(PlayerInventoryAC);

	PlayerInteractorAC = CreateDefaultSubobject<UPlayerInteractorAC>(TEXT("Player Interactor"));
	AddOwnedComponent(PlayerInteractorAC);
}

void APastaWaterPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	InitialiseInventory();
}

void APastaWaterPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Input binds
	if(InputComponent)
	{
		InputComponent->BindAction("ToggleInventory", IE_Pressed, this, &APastaWaterPlayerControllerBase::PerformToggleInventoryAction);
		InputComponent->BindAction("Jump", IE_Pressed, this, &APastaWaterPlayerControllerBase::PerformJumpAction);
		InputComponent->BindAction("Primary", IE_Pressed, this, &APastaWaterPlayerControllerBase::PerformPrimaryAction);
		InputComponent->BindAxis("MoveForwardBackward", this, &APastaWaterPlayerControllerBase::PerformMoveForwardBackward);
		InputComponent->BindAxis("MoveRightLeft", this, &APastaWaterPlayerControllerBase::PerformMoveRightLeft);
		InputComponent->BindAxis("LookPitch", this, &APastaWaterPlayerControllerBase::PerformLookPitch);
		InputComponent->BindAxis("LookYaw", this, &APastaWaterPlayerControllerBase::PerformLookYaw);
	}
}

void APastaWaterPlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UDebugHelpers::ScreenLogInfo("Player controller "+GetName()+" has possessed "+InPawn->GetName());;
}

void APastaWaterPlayerControllerBase::OnUnPossess()
{
	Super::OnUnPossess();
	UDebugHelpers::ScreenLogInfo("Player controller "+GetName()+" has unpossessed.");
}

APastaWaterPlayerControllerBase* APastaWaterPlayerControllerBase::CastFromActor(AActor* Actor)
{
	if(!IsValid(Actor))
	{
		UDebugHelpers::ScreenLogError("Actor is null.");
		return nullptr;
	}
	
	APastaWaterPlayerControllerBase* PastaWaterPlayerController = Cast<APastaWaterPlayerControllerBase>(Actor);
	if(!IsValid(PastaWaterPlayerController))
	{
		UDebugHelpers::ScreenLogInfo("Actor could not be casted into Pasta Water Player Controller.");
		return nullptr;
	}

	return PastaWaterPlayerController;
}

APastaWaterPlayerControllerBase* APastaWaterPlayerControllerBase::CastFromPlayerController(
	APlayerController* PlayerController)
{
	if(!IsValid(PlayerController))
	{
		UDebugHelpers::ScreenLogError("Player Controller is null.");
		return nullptr;
	}
	
	APastaWaterPlayerControllerBase* PastaWaterPlayerController = Cast<APastaWaterPlayerControllerBase>(PlayerController);
	if(!IsValid(PastaWaterPlayerController))
	{
		UDebugHelpers::ScreenLogError("Player Controller could not be casted into Pasta Water Player Controller.");
		return nullptr;
	}

	return PastaWaterPlayerController;
}

void APastaWaterPlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APastaWaterPlayerControllerBase::PerformJumpAction()
{
	if(!JumpActionEnabled) return;
	if(!IsValid(PastaWaterCharacter)) return;
	IMovableInterface::Execute_PerformJumpAction(PastaWaterCharacter);
}

void APastaWaterPlayerControllerBase::PerformPrimaryAction()
{
	if(!PrimaryActionEnabled) { return; }
	IInteractorInterface::Execute_Interact(PlayerInteractorAC, nullptr);
}

void APastaWaterPlayerControllerBase::PerformToggleInventoryAction()
{
	ToggleInventory();
}

void APastaWaterPlayerControllerBase::PerformMoveRightLeft(const float AxisValue)
{
	if(!MovementEnabled) { return; }
	if(!IsValid(PastaWaterCharacter)) return;
	IMovableInterface::Execute_PerformMoveRightLeft(PastaWaterCharacter, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformMoveForwardBackward(const float AxisValue)
{
	if(!MovementEnabled) { return; }
	if(!IsValid(PastaWaterCharacter)) return;
	IMovableInterface::Execute_PerformMoveForwardBackward(PastaWaterCharacter, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformLookPitch(const float AxisValue)
{
	if(!LookingEnabled) { return; }
	if(!IsValid(PastaWaterCharacter)) return;
	IMovableInterface::Execute_PerformLookPitch(PastaWaterCharacter, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformLookYaw(const float AxisValue)
{
	if(!LookingEnabled) { return; }
	if(!IsValid(PastaWaterCharacter)) return;
	IMovableInterface::Execute_PerformLookYaw(PastaWaterCharacter, AxisValue);
}

UPlayerInventoryAC* APastaWaterPlayerControllerBase::GetInventoryACOrDefault() const
{
	if(!IsValid(PlayerInventoryAC))
	{
		UDebugHelpers::ScreenLogError("Player needs to have an Inventory!");
		return nullptr;
	}
	return PlayerInventoryAC;
}

void APastaWaterPlayerControllerBase::FlushInputs()
{
	PlayerInput->FlushPressedKeys();
}

void APastaWaterPlayerControllerBase::DisableAllInputs()
{
	LookingEnabled = false;
	MovementEnabled = false;
	JumpActionEnabled = false;
	PrimaryActionEnabled = false;
}

void APastaWaterPlayerControllerBase::EnableAllInputs()
{
	LookingEnabled = true;
	MovementEnabled = true;
	JumpActionEnabled = true;
	PrimaryActionEnabled = true;
}

void APastaWaterPlayerControllerBase::InitialiseInventory_Implementation()
{
	PlayerInventoryWidget = UPlayerInventoryWidget::Create(PlayerInventoryWidgetClass, this);
}

void APastaWaterPlayerControllerBase::ToggleInventory_Implementation()
{
	if(!IsValid(PlayerInventoryWidget))
	{
		UDebugHelpers::ScreenLogError("Player Inventory Widget was not set up properly!");
		return;
	}
	
	PlayerInventoryWidget->UpdateInventorySlots();

	if(PlayerInventoryWidget->IsVisible())
	{
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		FlushInputs();
		SetInputMode(FInputModeGameOnly());
		EnableAllInputs();
		SetShowMouseCursor(false);
		UDebugHelpers::ScreenLogInfo("Player Inventory UI hidden.");
	} else
	{
		PlayerInventoryWidget->SetVisibility(ESlateVisibility::Visible);
		FlushInputs();
		DisableAllInputs();

		// Input mode
		FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		InputMode.SetWidgetToFocus(PlayerInventoryWidget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
		
		SetShowMouseCursor(true);
		UDebugHelpers::ScreenLogInfo("Player Inventory UI showed.");
	}
}

void APastaWaterPlayerControllerBase::ToggleWidgetFocus(UWidget* Widget)
{
	if(Widget->IsVisible())
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
		FlushInputs();
		SetInputMode(FInputModeGameOnly());
		EnableAllInputs();
		SetShowMouseCursor(false);
		UDebugHelpers::ScreenLogInfo("Player Inventory UI hidden.");
	} else
	{
		Widget->SetVisibility(ESlateVisibility::Visible);
		FlushInputs();
		DisableAllInputs();

		// Input mode
		FInputModeGameAndUI InputMode = FInputModeGameAndUI();
		InputMode.SetWidgetToFocus(Widget->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockInFullscreen);
		InputMode.SetHideCursorDuringCapture(false);
		SetInputMode(InputMode);
		
		SetShowMouseCursor(true);
		UDebugHelpers::ScreenLogInfo("Player Inventory UI showed.");
	}
}
