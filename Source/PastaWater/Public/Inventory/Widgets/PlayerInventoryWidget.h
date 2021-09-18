﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStackSlotWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Inventory/ActorComponents/PlayerInventoryAC.h"
#include "PlayerInventoryWidget.generated.h"

class APastaWaterPlayerControllerBase;
/**
 * Widget which displays a player's inventory and hotbar.
 */
UCLASS()
class PASTAWATER_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	int Columns = 10;
	int Rows = 5;
	
public:
	UPROPERTY(BlueprintReadWrite)
	APastaWaterPlayerControllerBase* PlayerController; 

	UPROPERTY(BlueprintReadWrite)
	UPlayerInventoryAC* PlayerInventoryAC;

	UPROPERTY(BlueprintReadWrite)
	UGridPanel* PlayerItemsGridPanel;
	
	// Panel which contains items
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* ItemsGridPanel;

	/**
	 * Populate this in the editor. Determines the class of the Item Stack Slot.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemStackSlotWidget> ItemStackSlotClass;

	UFUNCTION(BlueprintCallable)
	bool Initialise();
	
	UFUNCTION(BlueprintCallable)
	bool CreateInventorySlots();

	UFUNCTION(BlueprintCallable)
	bool UpdateInventorySlots();

private:
	// Get Items Grid Panel with null check
	UGridPanel* GetItemsGridPanel() const;
};