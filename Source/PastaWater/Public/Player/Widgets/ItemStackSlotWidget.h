#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Core/Inventory/Interfaces/InventoryInterface.h"
#include "ItemStackSlotWidget.generated.h"

/**
 * Represents an item slot in an inventory.
 */
UCLASS(BlueprintType, Blueprintable)
class PASTAWATER_API UItemStackSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual bool Initialize() override;
	
public:
	// Properties that give information about item stack
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<IInventoryInterface> InventoryAC;
	UPROPERTY(BlueprintReadWrite)
	int InventoryACIndex;

	// Main panel
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UCanvasPanel* MainPanel;

	// Background panel
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UBorder* BackgroundPanel;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* BackgroundImage;

	// Item image panel
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UBorder* ItemImagePanel;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* ItemImage;
	
	// Item details panel
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UVerticalBox* ItemDetailsPanel;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ItemNameText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* ItemQuantityText;

	UFUNCTION(BlueprintCallable)
	void UpdateItemDetails();

private:
	FItemStack GetItemDetails() const;
};
