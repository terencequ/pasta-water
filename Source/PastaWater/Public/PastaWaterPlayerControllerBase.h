// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Inventory/ActorComponents/PlayerInventoryAC.h"
#include "Movement/ActorComponents/PlayerMovableAC.h"

#include "PastaWaterPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PASTAWATER_API APastaWaterPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	UPlayerInventoryAC* PlayerInventoryAC;
	
	UPROPERTY(BlueprintReadWrite)
	bool LookingEnabled = true;
	UPROPERTY(BlueprintReadWrite)
	bool MovementEnabled = true;
	UPROPERTY(BlueprintReadWrite)
	bool PrimaryActionEnabled = true;
	UPROPERTY(BlueprintReadWrite)
	bool JumpActionEnabled = true;


public:
	// Sets default values for this character's properties
	APastaWaterPlayerControllerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PerformJumpAction();

	void PerformPrimaryAction();

	void PerformMoveRightLeft(float AxisValue);
	
	void PerformMoveForwardBackward(float AxisValue);

	void PerformLookPitch(float AxisValue);

	void PerformLookYaw(float AxisValue);

	UPlayerInventoryAC* GetInventoryAC() const;
};
