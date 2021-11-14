// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/Models/Item.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameStateBase.h"
#include "PastaWaterGameState.generated.h"

/**
 * Holds state of the game that should be replicated to all clients and server.
 */
UCLASS()
class PASTAWATER_API APastaWaterGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	/**
	 * @brief Populate this in blueprints, it contains a definition of all valid items
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Definitions")
	UDataTable* ItemDefinitions;

	/**
	 * @brief Find an item in the item definition table by Item Id.
	 */
	FItem* FindItem(FString ItemId) const;

	/**
	 * @brief Get the GameState with null and casting checks.
	 */
	static APastaWaterGameState* GetGameState(const UObject* Object);
};
