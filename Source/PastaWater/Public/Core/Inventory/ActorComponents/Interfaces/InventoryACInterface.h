// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Core/Inventory/Models/Structs/ItemStack.h"
#include "UObject/Interface.h"
#include "InventoryACInterface.generated.h"

UINTERFACE()
class UInventoryACInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for an actor component which manages an inventory.
 */
class PASTAWATER_API IInventoryACInterface
{
	GENERATED_BODY()

public:
	/**
	 * @brief Get an item stack at index.
	 * Index starts at 0. If no item can be found, return null.
	 * @param Index Index of list
	 * @return ItemStack
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Single Slot")
	FItemStack GetItemStackAtIndex(const int Index) const;
	
	/**
	 * @brief Set an item stack at index.
	 * Index starts at 0. If index is out of range, return null.
	 * @param Index Index of list
	 * @param ItemStack New item stack
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Single Slot")
	void SetItemStackAtIndex(const int Index, const FItemStack ItemStack);
	
	/**
	 * @brief Get the size of the item list.
	 * @return Total count of items
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Properties")
	int GetContainerSize() const;

	/**
	 * @brief Swap two item stacks.
	 * @param FirstIndex First item stack index
	 * @param SecondIndex Second item stack index
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	void SwapItemStacks(const int FirstIndex, const int SecondIndex);
	
	/**
	 * @brief Check if an item stack can be inserted into this inventory without overflowing.
	 * @param ItemStack Item stack to insert
	 * @return True if stack there is enough space for items. False otherwise.
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Checks")
	bool CanInsertItemStack(const FItemStack ItemStack) const;
	
	/**
	 * @brief Insert an item stack into this inventory.
	 * Any quantity of items that could not be inserted will be returned from this method as an ItemStack.
	 * @param ItemStack Item stack to insert
	 * @return Overflow item stack
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	FItemStack InsertItemStack(const FItemStack ItemStack);

	/**
	* @brief Check if an item stack can be removed from this inventory in its entirety.
	* @param ItemStack Item stack to insert
	* @return True if there are enough items to remove. False otherwise.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Checks")
	bool CanRemoveItemStack(const FItemStack ItemStack) const;
	
	/**
	 * @brief Remove an item stack from this inventory.
	 * Returns a stack representing the items removed.
	 * If all items could not be removed, use the stack to compare what was removed.
	 * @param ItemStack Item stack to insert
	 * @return Items that were removed
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory Actions")
	FItemStack RemoveItemStack(const FItemStack ItemStack);
	
	/**
	 * @brief Get all item stacks part of this inventory.
	 * Returns a TArray of item stacks representing the items in the inventory.
	 * @return All items
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory All Slots")
	TArray<FItemStack> GetAllItemStacks() const;

	/**
	 * @brief Remove all item stacks part of this inventory
	 * @return All item stacks that were removed
	 */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Inventory All Slots")
	TArray<FItemStack> RemoveAllItemStacks();
};
