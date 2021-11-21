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

public:
	UFUNCTION(BlueprintCallable)
	virtual bool CreateInventorySlots(const FString WidgetId) override;

	UFUNCTION(BlueprintCallable)
	virtual bool UpdateInventorySlots() override;
	
	static UPlayerHotbarWidget* Create(TSubclassOf<UPlayerHotbarWidget> PlayerInventoryWidgetClass,
	                            APastaWaterPlayerControllerBase* OwningPlayerController,
	                            UPlayerInventoryAC* OwningPlayerInventoryAC);
};
