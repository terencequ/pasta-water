// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PastaWaterCharacterBase.h"
#include "GameFramework/PlayerController.h"
#include "Interact/ActorComponents/PlayerInteractorAC.h"
#include "Inventory/ActorComponents/PlayerInventoryAC.h"
#include "Inventory/ActorComponents/PlayerInventoryDisplayAC.h"
#include "PastaWaterPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PASTAWATER_API APastaWaterPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category="Inventory Actor Components")
	APastaWaterCharacterBase* PastaWaterCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Actor Components")
	UPlayerInventoryAC* PlayerInventoryAC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Actor Components")
	UPlayerInventoryDisplayAC* PlayerInventoryDisplayAC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Interaction Actor Components")
	UPlayerInteractorAC* PlayerInteractorAC;
	
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
	static APastaWaterPlayerControllerBase* CastFromActor(AActor* Actor);

	static APastaWaterPlayerControllerBase* CastFromPlayerController(APlayerController* PlayerController);
	
	virtual void Tick(float DeltaTime) override;

	void PerformJumpAction();

	void PerformPrimaryAction();
	
	void PerformToggleInventoryAction();

	void PerformMoveRightLeft(float AxisValue);
	
	void PerformMoveForwardBackward(float AxisValue);

	void PerformLookPitch(float AxisValue);

	void PerformLookYaw(float AxisValue);

	UPlayerInventoryAC* GetInventoryACOrDefault() const;

	/**
	 * Clear out all current pressed keys.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	void FlushInputs();

	/**
	 * Disallow any more inputs from occurring, i.e. looking, movement, actions.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	void DisableAllInputs();

	/**
	 * Allow all inputs from occurring, used to reenable after using DisableAllInputs.
	 */
	UFUNCTION(BlueprintCallable, Category="Inputs")
	void EnableAllInputs();
};
