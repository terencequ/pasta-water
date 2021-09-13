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
	PrimaryActionEnabled = true;
	JumpActionEnabled = true;

	// Input binds
	if(InputComponent)
	{
		InputComponent->BindAction("JumpAction", IE_Pressed, this, &APastaWaterPlayerControllerBase::PerformJumpAction);
		InputComponent->BindAction("PrimaryAction", IE_Pressed, this, &APastaWaterPlayerControllerBase::PerformPrimaryAction);
		InputComponent->BindAxis("MoveForwardBackward", this, &APastaWaterPlayerControllerBase::PerformMoveForwardBackward);
		InputComponent->BindAxis("MoveRightLeft", this, &APastaWaterPlayerControllerBase::PerformMoveRightLeft);
		InputComponent->BindAxis("PerformLookPitch", this, &APastaWaterPlayerControllerBase::PerformLookPitch);
		InputComponent->BindAxis("PerformLookYaw", this, &APastaWaterPlayerControllerBase::PerformLookYaw);
	}
}

void APastaWaterPlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APastaWaterPlayerControllerBase::PerformJumpAction()
{
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformJumpAction(PastaWaterCharacter->PlayerMovableAC);
}

void APastaWaterPlayerControllerBase::PerformPrimaryAction()
{
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
}

void APastaWaterPlayerControllerBase::PerformMoveRightLeft(float AxisValue)
{
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformMoveRightLeft(PastaWaterCharacter->PlayerMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformMoveForwardBackward(float AxisValue)
{
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformMoveForwardBackward(PastaWaterCharacter->PlayerMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformLookPitch(float AxisValue)
{
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformLookPitch(PastaWaterCharacter->PlayerMovableAC, AxisValue);
}

void APastaWaterPlayerControllerBase::PerformLookYaw(float AxisValue)
{
	APastaWaterCharacterBase* PastaWaterCharacter = Cast<APastaWaterCharacterBase>(GetCharacter());
	UPlayerMovableAC::Execute_PerformLookYaw(PastaWaterCharacter->PlayerMovableAC, AxisValue);
}


