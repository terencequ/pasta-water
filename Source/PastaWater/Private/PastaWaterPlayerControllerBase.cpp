// Fill out your copyright notice in the Description page of Project Settings.


#include "PastaWaterPlayerControllerBase.h"

#include "PastaWaterCharacterBase.h"

APastaWaterPlayerControllerBase::APastaWaterPlayerControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
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

void APastaWaterPlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APastaWaterPlayerControllerBase::PerformJumpAction()
{
	if(!JumpActionEnabled) { return; }
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformJumpAction(PastaWaterCharacter->PlayerMovableAC);
}

void APastaWaterPlayerControllerBase::PerformPrimaryAction()
{
	if(!PrimaryActionEnabled) { return; }
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Primary action pressed."));    
}

void APastaWaterPlayerControllerBase::PerformMoveRightLeft(float AxisValue)
{
	if(!MovementEnabled) { return; }
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformMoveRightLeft(PastaWaterCharacter->PlayerMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformMoveForwardBackward(float AxisValue)
{
	if(!MovementEnabled) { return; }
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformMoveForwardBackward(PastaWaterCharacter->PlayerMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformLookPitch(float AxisValue)
{
	if(!LookingEnabled) { return; }
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformLookPitch(PastaWaterCharacter->PlayerMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformLookYaw(float AxisValue)
{
	if(!LookingEnabled) { return; }
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformLookYaw(PastaWaterCharacter->PlayerMovableAC, AxisValue);
}


