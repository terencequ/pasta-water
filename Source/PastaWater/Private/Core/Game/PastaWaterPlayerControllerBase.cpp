#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Core/Pawns/Interfaces/MovableInterface.h"
#include "GameFramework/PlayerInput.h"

APastaWaterPlayerControllerBase::APastaWaterPlayerControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMinNetUpdateFrequency(2.0f);
	SetNetUpdateFrequency(10.0f);
}

void APastaWaterPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APastaWaterPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Cast to Enhanced Input Component
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &APastaWaterPlayerControllerBase::PerformMove);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &APastaWaterPlayerControllerBase::PerformLook);
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &APastaWaterPlayerControllerBase::PerformJump);
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
void APastaWaterPlayerControllerBase::PerformJump(const FInputActionValue& Value)
{
	if(!JumpActionEnabled) return;
	if(!IsValid(PastaWaterCharacter)) return;
	IMovableInterface::Execute_PerformJump(PastaWaterCharacter);
}

void APastaWaterPlayerControllerBase::PerformMove(const FInputActionValue& Value)
{
	if(!MovementEnabled) { return; }
	if(!IsValid(PastaWaterCharacter)) return;
	FVector2D MoveValue = Value.Get<FVector2D>();
	IMovableInterface::Execute_PerformMoveRightLeft(PastaWaterCharacter, MoveValue.X);
	IMovableInterface::Execute_PerformMoveForwardBackward(PastaWaterCharacter, MoveValue.Y);
}

void APastaWaterPlayerControllerBase::PerformLook(const FInputActionValue& Value)
{
	if(!LookingEnabled) { return; }
	if(!IsValid(PastaWaterCharacter)) return;
	FVector2D LookValue = Value.Get<FVector2D>();
	IMovableInterface::Execute_PerformLookYaw(PastaWaterCharacter, LookValue.X);
	IMovableInterface::Execute_PerformLookPitch(PastaWaterCharacter, LookValue.Y * -1);
}

// Input control
void APastaWaterPlayerControllerBase::FlushInputs()
{
	PlayerInput->FlushPressedKeys();
}

void APastaWaterPlayerControllerBase::DisableAllInputs()
{
	FlushInputs();
	LookingEnabled = false;
	MovementEnabled = false;
	JumpActionEnabled = false;
}

void APastaWaterPlayerControllerBase::EnableAllInputs()
{
	FlushInputs();
	LookingEnabled = true;
	MovementEnabled = true;
	JumpActionEnabled = true;
}

void APastaWaterPlayerControllerBase::ToggleWidgetVisibility(UWidget* Widget)
{
	if(Widget->IsVisible())
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
	} else
	{
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
}

void APastaWaterPlayerControllerBase::ToggleWidgetVisibilityAndFocus(UWidget* Widget)
{
	if(Widget->IsVisible())
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
		SetInputMode(FInputModeGameOnly());
		EnableAllInputs();
		SetShowMouseCursor(false);
	} else
	{
		Widget->SetVisibility(ESlateVisibility::Visible);
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
