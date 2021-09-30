#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Core/Pawns/Interfaces/MovableInterface.h"
#include "GameFramework/PlayerInput.h"

APastaWaterPlayerControllerBase::APastaWaterPlayerControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	MinNetUpdateFrequency = 2.0f;
	NetUpdateFrequency = 10.0f;
}

void APastaWaterPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
}

void APastaWaterPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	// Input binds
	if(InputComponent)
	{
		InputComponent->BindAction("Jump", IE_Pressed, this, &APastaWaterPlayerControllerBase::PerformJumpAction);
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

// Input bindings
void APastaWaterPlayerControllerBase::PerformJumpAction()
{
	if(!JumpActionEnabled) return;
	if(!IsValid(PastaWaterCharacter)) return;
	IMovableInterface::Execute_PerformJumpAction(PastaWaterCharacter);
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

// Input control
void APastaWaterPlayerControllerBase::FlushInputs()
{
	PlayerInput->FlushPressedKeys();
}

void APastaWaterPlayerControllerBase::DisableAllInputs()
{
	LookingEnabled = false;
	MovementEnabled = false;
	JumpActionEnabled = false;
}

void APastaWaterPlayerControllerBase::EnableAllInputs()
{
	LookingEnabled = true;
	MovementEnabled = true;
	JumpActionEnabled = true;
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
	}
}
