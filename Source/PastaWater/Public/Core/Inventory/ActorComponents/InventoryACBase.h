// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/Interfaces/InventoryInterface.h"
#include "Core/Inventory/Models/Interfaces/ItemStackContainerInterface.h"
#include "Engine/DataTable.h"
#include "InventoryACBase.generated.h"

/**
 * Base Actor Component for an Inventory.
 */
UCLASS()
class PASTAWATER_API UInventoryACBase : public UActorComponent, public IInventoryInterface
{
	GENERATED_BODY()
	
protected:
	/**
	* @brief This will keep track of the inventory's contents.
	*/
	UPROPERTY()
	TScriptInterface<IItemStackContainerInterface> Inventory;

public:
	/**
	 * @brief Populate this in blueprints, it contains a definition of all valid items
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Definitions")
	UDataTable* ItemDefinitions;
	
	UInventoryACBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							FActorComponentTickFunction* ThisTickFunction) override;

	virtual FItemStack GetItemStackAtIndex_Implementation(const int Index) const override;
	
	virtual void SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack) override;
	
	virtual int GetContainerSize_Implementation() const override;
	
	virtual void SwapItemStacks_Implementation(const int FirstIndex, const int SecondIndex) override;
	
	virtual bool CanInsertItemStack_Implementation(const FItemStack ItemStack) const override;
	
	virtual FItemStack InsertItemStack_Implementation(const FItemStack ItemStack) override;
	
	virtual bool CanRemoveItemStack_Implementation(const FItemStack ItemStack) const override;
	
	virtual FItemStack RemoveItemStack_Implementation(const FItemStack ItemStack) override;
	
	virtual TArray<FItemStack> GetAllItemStacks_Implementation() const override;
	
	virtual TArray<FItemStack> RemoveAllItemStacks_Implementation() override;
};
