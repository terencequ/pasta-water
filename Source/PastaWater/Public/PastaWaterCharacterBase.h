// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Movement/Interfaces/MovableInterface.h"

#include "PastaWaterCharacterBase.generated.h"

/**
 * Base class for pawns that can move around.
 */
UCLASS()
class PASTAWATER_API APastaWaterCharacterBase : public ACharacter, public IMovableInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MouseSensitivity = 1.0f;

	// Sets default values for this character's properties
	APastaWaterCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void PerformJumpAction_Implementation() override;
	
	virtual void PerformMoveForwardBackward_Implementation(const float AxisValue) override;
	
	virtual void PerformMoveRightLeft_Implementation(const float AxisValue) override;
	
	virtual void PerformLookPitch_Implementation(const float AxisValue) override;
	
	virtual void PerformLookYaw_Implementation(const float AxisValue) override;
};
