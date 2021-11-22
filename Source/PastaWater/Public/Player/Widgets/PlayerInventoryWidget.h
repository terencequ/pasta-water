﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidget.h"
#include "ItemStackSlotWidget.h"
#include "Components/SizeBox.h"
#include "Player/PlayerInventoryAC.h"
#include "PlayerInventoryWidget.generated.h"

class APastaWaterPlayerControllerBase;

/**
 * Widget which displays a player's inventory and mouse item stack.
 */
UCLASS()
class PASTAWATER_API UPlayerInventoryWidget : public UInventoryWidget
{
	GENERATED_BODY()

public:
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	// Main panel
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCanvasPanel* MainPanel;
	
	// Panel for hotbar item slots
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* HotbarItemsGridPanel;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	USizeBox* MouseSlotBox;
	
	UFUNCTION(BlueprintCallable)
	virtual bool CreateInventorySlots(const FString WidgetId) override;
	
	UFUNCTION(BlueprintCallable)
	virtual bool UpdateInventorySlots() override;
	
	/**
	 * Static constructor method to create an instance of a UPlayerInventoryWidget.
	 */
	UFUNCTION(BlueprintCallable)
	static UPlayerInventoryWidget* Create(
		TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass,
		APastaWaterPlayerControllerBase* OwningPlayerController,
		UPlayerInventoryAC* OwningPlayerInventoryAC);
};
