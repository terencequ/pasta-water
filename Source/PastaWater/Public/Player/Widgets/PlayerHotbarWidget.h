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
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* HotbarHighlighter;
	
	UFUNCTION(BlueprintCallable)
	virtual bool CreateInventorySlots(const FString WidgetId) override;

	UFUNCTION(BlueprintCallable)
	virtual bool UpdateInventorySlots() override;

	UFUNCTION(BlueprintCallable)
	void OnUpdateHotbarSelection(int CurrentSelectedHotbarIndex);
	
	UFUNCTION(BlueprintCallable)
	static UPlayerHotbarWidget* Create(TSubclassOf<UPlayerHotbarWidget> PlayerInventoryWidgetClass,
	                            APastaWaterPlayerControllerBase* OwningPlayerController,
	                            UPlayerInventoryAC* OwningPlayerInventoryAC);
};
