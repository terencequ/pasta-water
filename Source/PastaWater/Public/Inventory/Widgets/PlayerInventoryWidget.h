// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStackSlotWidget.h"
#include "PastaWaterPlayerControllerBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "Inventory/Models/Interfaces/ItemStackContainerInterface.h"
#include "PlayerInventoryWidget.generated.h"

/**
 * Widget which displays a player's inventory and hotbar.
 */
UCLASS()
class PASTAWATER_API UPlayerInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

	

private:
	int Columns = 10;
	int Rows = 5;
	
public:
	// Panel which contains items
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* ItemsGridPanel;

	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<UItemStackSlotWidget> ItemStackSlotClass;
	
	UFUNCTION(BlueprintCallable)
	bool CreateInventorySlots();

	UFUNCTION(BlueprintCallable)
	bool UpdateInventorySlots();

private:
	// Get owning Pasta Player Controller with null and cast checks
	APastaWaterPlayerControllerBase* GetOwningPastaPlayerController() const;

	// Get Items Grid Panel with null check
	UGridPanel* GetItemsGridPanel() const;
};
