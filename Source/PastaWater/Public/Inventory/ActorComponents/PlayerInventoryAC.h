// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InventoryACInterface.h"
#include "Inventory/Models/ItemStackContainerBase.h"
#include "Inventory/Models/Structs/ItemStack.h"

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

	UFUNCTION(BlueprintCallable, Category="Player Inventory Single Slot")
	virtual FItemStack GetItemStackAtIndex_Implementation(const int Index) const override;
	
	UFUNCTION(BlueprintCallable, Category="Player Inventory Single Slot")
	virtual void SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack) override;

	UFUNCTION(BlueprintCallable, Category="Player Inventory Actions")
	virtual void SwapItemStacks_Implementation(const int FirstIndex, const int SecondIndex) override;
	
	UFUNCTION(BlueprintCallable, Category="Player Inventory Actions")
	virtual bool CanInsertItemStack_Implementation(const FItemStack ItemStack) const override;

	UFUNCTION(BlueprintCallable, Category="Player Inventory Actions")
	virtual FItemStack InsertItemStack_Implementation(const FItemStack ItemStack) override;

	UFUNCTION(BlueprintCallable, Category="Player Inventory Actions")
	virtual bool CanRemoveItemStack_Implementation(const FItemStack ItemStack) const override;

	UFUNCTION(BlueprintCallable, Category="Player Inventory Actions")
	virtual FItemStack RemoveItemStack_Implementation(const FItemStack ItemStack) override;

	UFUNCTION(BlueprintCallable, Category="Player Inventory All Slots")
	virtual TArray<FItemStack> GetAllItemStacks_Implementation() const override;

	UFUNCTION(BlueprintCallable, Category="Player Inventory All Slots")
	virtual TArray<FItemStack> RemoveAllItemStacks_Implementation() override;
};
