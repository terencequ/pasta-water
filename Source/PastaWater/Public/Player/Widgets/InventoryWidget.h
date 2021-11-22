#pragma once

#include "CoreMinimal.h"
#include "ItemStackSlotWidget.h"
#include "Components/GridPanel.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "Core/Inventory/Models/ItemStack.h"
#include "Player/PlayerInventoryAC.h"
#include "InventoryWidget.generated.h"

/**
 * Base class for inventory-style widgets.
 */
UCLASS(Blueprintable)
class PASTAWATER_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Index to start with for connecting inventory slots to InventoryAC.
	UPROPERTY(EditAnywhere)
	int StartIndex = 0;
	
	UPROPERTY(EditAnywhere)
	int Columns = 10;
	
	UPROPERTY(EditAnywhere)
	int Rows = 5;
	
public:
	UPROPERTY(BlueprintReadWrite)
	APastaWaterPlayerControllerBase* PlayerController; 

	UPROPERTY(BlueprintReadWrite)
	UInventoryACBase* InventoryAC;

	// Panel for item slots
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UGridPanel* ItemsGridPanel;
	
	/**
	 * Populate this in the editor. Determines the class of the Item Stack Slot.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemStackSlotWidget> ItemStackSlotClass;
	
	/**
	 * Populate this in the editor. Determines the class of the Item Stack Slot.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UItemStackSlotWidget> MouseItemStackSlotClass;
	
	UFUNCTION(BlueprintCallable)
	bool Setup(UInventoryACBase* OwningInventoryAC);

	virtual bool OpenInventory();
	
	virtual bool CloseInventory();
	
	virtual bool CreateInventorySlots(const FString WidgetId);
	
	virtual bool UpdateInventorySlots();

	/**
	 * Callback for closing inventory.
	 */
	UFUNCTION(BlueprintCallable)
	void OnCloseInventory();
	
	/**
	 * Callback for FUpdateInventoryDelegate from Inventory
	 */
	UFUNCTION(BlueprintCallable)
	void OnUpdateInventorySlots(const TArray<FItemStack> ItemStacks);
};
