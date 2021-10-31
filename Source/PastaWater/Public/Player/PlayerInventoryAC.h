// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/ActorComponents/InventoryACBase.h"

#include "PlayerInventoryAC.generated.h"


/**
 * @brief This actor component represents the player's inventory.
 * The player has several equip slots (left hand, right hand) and a main inventory.
 */
UCLASS(Blueprintable)
class PASTAWATER_API UPlayerInventoryAC : public UInventoryACBase
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UPlayerInventoryAC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
