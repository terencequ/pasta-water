#include "PastaWaterCharacterBase.h"
#include "Kismet/KismetMathLibrary.h"

APastaWaterCharacterBase::APastaWaterCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicatingMovement(true);
}

void APastaWaterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void APastaWaterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APastaWaterCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APastaWaterCharacterBase::PerformJumpAction_Implementation()
{
	Jump();
}

void APastaWaterCharacterBase::PerformMoveForwardBackward_Implementation(const float AxisValue)
{
	const FRotator Rotator = FRotator(0, Controller->GetControlRotation().Yaw, 0); // Get yaw
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotator); // Get forward vector based on yaw
	AddMovementInput(ForwardVector, AxisValue, true); // Move towards forward vector
}

void APastaWaterCharacterBase::PerformMoveRightLeft_Implementation(const float AxisValue)
{
	const FRotator Rotator = FRotator(0, Controller->GetControlRotation().Yaw, 0); // Get yaw
	const FVector RightVector = UKismetMathLibrary::GetRightVector(Rotator); // Get forward vector based on yaw
	AddMovementInput(RightVector, AxisValue, true); // Move towards right vector
}

void APastaWaterCharacterBase::PerformLookPitch_Implementation(const float AxisValue)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(!PlayerController) { return; }

	PlayerController->AddPitchInput(AxisValue * MouseSensitivity);
}

void APastaWaterCharacterBase::PerformLookYaw_Implementation(const float AxisValue)
{
	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if(!PlayerController) { return; }

	PlayerController->AddYawInput(AxisValue * MouseSensitivity);
}
