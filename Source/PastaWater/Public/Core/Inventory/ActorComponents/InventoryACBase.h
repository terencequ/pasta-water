// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/Interfaces/InventoryInterface.h"
#include "Core/Inventory/Models/ItemStack.h"
#include "InventoryACBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateInventoryDelegate, const TArray<FItemStack>);

/**
 * Base Actor Component for an Inventory.
 */
UCLASS()
class PASTAWATER_API UInventoryACBase : public UActorComponent, public IInventoryInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(ReplicatedUsing=OnRep_MaxInventorySize)
	int MaxInventorySize;

	UPROPERTY(ReplicatedUsing=OnRep_ItemStacks)
	TArray<FItemStack> ItemStacks;

public:
	FUpdateInventoryDelegate UpdateInventoryDelegate;
	
	UInventoryACBase();

protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							FActorComponentTickFunction* ThisTickFunction) override;
	
	void Init(int Size);

	// Networking
	UFUNCTION()
	void OnRep_MaxInventorySize();

	UFUNCTION()
	void OnRep_ItemStacks();

	// Functionality
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
	
	/**
	 * @brief Lookup item in the current GameState.
	 */
	FItem* FindItem(const FString ItemId) const;
	
private:
	/**
	 * @brief Update the item slot. This should perform any cleanup actions needed,
	 * i.e. making the slot into a null item if the quantity/durability is 0.
	 * @param Index Index of slot to update
	 */
	void UpdateItemSlot(const int Index);
};
