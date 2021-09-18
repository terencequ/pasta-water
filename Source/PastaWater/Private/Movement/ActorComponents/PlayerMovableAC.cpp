#include "Movement/ActorComponents/PlayerMovableAC.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UPlayerMovableAC::UPlayerMovableAC()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMovableAC::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerMovableAC::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UPlayerMovableAC::PerformJumpAction_Implementation()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character){	return; }
	
	Character->Jump();
}

void UPlayerMovableAC::PerformMoveForwardBackward_Implementation(const float AxisValue)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character){	return; }
	AController* Controller = Character->Controller;
	if(!Controller) { return; }

	const FRotator Rotator = FRotator(0, Controller->GetControlRotation().Yaw, 0); // Get yaw
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(Rotator); // Get forward vector based on yaw
	Character->AddMovementInput(ForwardVector, AxisValue, true); // Move towards forward vector
}

void UPlayerMovableAC::PerformMoveRightLeft_Implementation(const float AxisValue)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character){	return; }
	AController* Controller = Character->Controller;
	if(!Controller) { return; }

	const FRotator Rotator = FRotator(0, Controller->GetControlRotation().Yaw, 0); // Get yaw
	const FVector RightVector = UKismetMathLibrary::GetRightVector(Rotator); // Get forward vector based on yaw
	Character->AddMovementInput(RightVector, AxisValue, true); // Move towards right vector
}

void UPlayerMovableAC::PerformLookPitch_Implementation(const float AxisValue)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character){	return; }
	APlayerController* Controller = Cast<APlayerController>(Character->Controller);
	if(!Controller) { return; }

	Controller->AddPitchInput(AxisValue * MouseSensitivity);
}

void UPlayerMovableAC::PerformLookYaw_Implementation(const float AxisValue)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character){	return; }
	APlayerController* Controller = Cast<APlayerController>(Character->Controller);
	if(!Controller) { return; }

	Controller->AddYawInput(AxisValue * MouseSensitivity);
}

