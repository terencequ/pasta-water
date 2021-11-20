// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStackSlotWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Core/Interact/Interfaces/InteractableInterface.h"
#include "Player/PlayerInventoryAC.h"
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
	UPlayerInventoryAC* InventoryAC;

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

	/**
	 * Static constructor method to create an instance of a UPlayerInventoryWidget.
	 */
	UFUNCTION(BlueprintCallable)
	static UPlayerInventoryWidget* Create(
		TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass,
		APastaWaterPlayerControllerBase* OwningPlayerController,
		UPlayerInventoryAC* OwningPlayerInventoryAC);
	
	UFUNCTION(BlueprintCallable)
	bool Setup(UPlayerInventoryAC* OwningPlayerInventoryAC);
	
	UFUNCTION(BlueprintCallable)
	bool CreateInventorySlots();

	UFUNCTION(BlueprintCallable)
	bool UpdateInventorySlots();

	/**
	 * Callback for FUpdateInventoryDelegate from Inventory
	 */
	UFUNCTION(BlueprintCallable)
	void OnUpdateInventorySlots(const TArray<FItemStack> ItemStacks);

private:
	// Get Items Grid Panel with null check
	UGridPanel* GetItemsGridPanel() const;
};
