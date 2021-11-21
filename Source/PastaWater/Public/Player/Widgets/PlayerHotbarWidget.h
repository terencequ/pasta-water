// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidget.h"
#include "PlayerHotbarWidget.generated.h"

/**
 * Widget which displays a player's hotbar and keeps track of the active item.
 */
UCLASS()
class PASTAWATER_API UPlayerHotbarWidget : public UInventoryWidget
{
	GENERATED_BODY()
	
protected:
	int StartIndex = 0;
	int Columns = 10;
	int Rows = 1;

public:
	static UPlayerHotbarWidget* Create(TSubclassOf<UPlayerHotbarWidget> PlayerInventoryWidgetClass,
	                            APastaWaterPlayerControllerBase* OwningPlayerController,
	                            UPlayerInventoryAC* OwningPlayerInventoryAC);
};
