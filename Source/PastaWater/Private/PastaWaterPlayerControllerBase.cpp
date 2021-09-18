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

	PlayerInventoryDisplayAC = CreateDefaultSubobject<UPlayerInventoryDisplayAC>(TEXT("Player Inventory Display"));
	AddOwnedComponent(PlayerInventoryDisplayAC);

	PlayerInteractorAC = CreateDefaultSubobject<UPlayerInteractorAC>(TEXT("Player Interactor"));
	AddOwnedComponent(PlayerInventoryDisplayAC);
}

void APastaWaterPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
	// Input binds
	if(InputComponent)
	{
		InputComponent->BindAction("Jump", IE_Pressed, this, &APastaWaterPlayerControllerBase::PerformJumpAction);
		InputComponent->BindAction("Primary", IE_Pressed, this, &APastaWaterPlayerControllerBase::PerformPrimaryAction);
		InputComponent->BindAxis("MoveForwardBackward", this, &APastaWaterPlayerControllerBase::PerformMoveForwardBackward);
		InputComponent->BindAxis("MoveRightLeft", this, &APastaWaterPlayerControllerBase::PerformMoveRightLeft);
		InputComponent->BindAxis("LookPitch", this, &APastaWaterPlayerControllerBase::PerformLookPitch);
		InputComponent->BindAxis("LookYaw", this, &APastaWaterPlayerControllerBase::PerformLookYaw);
	}
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
	if(!JumpActionEnabled) { return; }
	const APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UCharacterMovableAC::Execute_PerformJumpAction(PastaWaterCharacter->CharacterMovableAC);
}

void APastaWaterPlayerControllerBase::PerformPrimaryAction()
{
	if(!PrimaryActionEnabled) { return; }
	IInteractorInterface::Execute_Interact(PlayerInteractorAC, nullptr);

	UDebugHelpers::ScreenLogInfo("Adding test items to inventory.");
	const FItem TestItem = *PlayerInventoryAC->ItemDefinitions->FindRow<FItem>("Test", "");
	IInventoryACInterface::Execute_InsertItemStack(PlayerInventoryAC, FItemStack(TestItem, 3));
}

void APastaWaterPlayerControllerBase::PerformMoveRightLeft(const float AxisValue)
{
	if(!MovementEnabled) { return; }
	const APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UCharacterMovableAC::Execute_PerformMoveRightLeft(PastaWaterCharacter->CharacterMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformMoveForwardBackward(const float AxisValue)
{
	if(!MovementEnabled) { return; }
	const APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UCharacterMovableAC::Execute_PerformMoveForwardBackward(PastaWaterCharacter->CharacterMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformLookPitch(const float AxisValue)
{
	if(!LookingEnabled) { return; }
	const APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UCharacterMovableAC::Execute_PerformLookPitch(PastaWaterCharacter->CharacterMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformLookYaw(const float AxisValue)
{
	if(!LookingEnabled) { return; }
	const APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UCharacterMovableAC::Execute_PerformLookYaw(PastaWaterCharacter->CharacterMovableAC, AxisValue);
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

