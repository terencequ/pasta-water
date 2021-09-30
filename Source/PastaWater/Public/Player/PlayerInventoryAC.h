// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Inventory/ActorComponents/Interfaces/InventoryACInterface.h"
#include "Core/Inventory/Models/Interfaces/ItemStackContainerInterface.h"

#include "PlayerInventoryAC.generated.h"


/**
 * @brief This actor component represents the player's inventory.
 * The player has several equip slots (left hand, right hand) and a main inventory.
 */
UCLASS(Blueprintable)
class PASTAWATER_API UPlayerInventoryAC : public UActorComponent, public IInventoryACInterface
{
	GENERATED_BODY()

private:
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
	
	// Sets default values for this component's properties
	UPlayerInventoryAC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	
	// Called every frame
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
