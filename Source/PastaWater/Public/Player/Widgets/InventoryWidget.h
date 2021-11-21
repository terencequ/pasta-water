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

protected:
	// Index to start with for connecting inventory slots to InventoryAC.
	int StartIndex = 0;
	int Columns = 10;
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
	
	UFUNCTION(BlueprintCallable)
	bool Setup(UInventoryACBase* OwningInventoryAC);
	
	UFUNCTION(BlueprintCallable)
	bool CreateInventorySlots();

	UFUNCTION(BlueprintCallable)
	bool UpdateInventorySlots();

	/**
	 * Callback for FUpdateInventoryDelegate from Inventory
	 */
	UFUNCTION(BlueprintCallable)
	void OnUpdateInventorySlots(const TArray<FItemStack> ItemStacks);
};
