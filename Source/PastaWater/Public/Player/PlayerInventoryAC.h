// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/ActorComponents/InventoryACBase.h"

#include "PlayerInventoryAC.generated.h"


/**
 * @brief This actor component represents the player's inventory.
 * The player has several equip slots (left hand, right hand) and a main inventory.
 */
UCLASS(Blueprintable)
class PASTAWATER_API UPlayerInventoryAC : public UInventoryACBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(ReplicatedUsing=OnRep_MaxHotbarSize)
	int MaxHotbarSize;

	UPROPERTY(ReplicatedUsing=OnRep_HotbarItemStacks)
	TArray<FItemStack> HotbarItemStacks;

	UPROPERTY(ReplicatedUsing=OnRep_MouseItemStack)
	FItemStack MouseItemStack;
	
public:
	// Sets default values for this component's properties
	UPlayerInventoryAC();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Init(int HotbarSize, int InventorySize);
public:
	// Networking
	UFUNCTION()
	void OnRep_MaxHotbarSize();

	UFUNCTION()
	void OnRep_HotbarItemStacks();

	UFUNCTION()
	void OnRep_MouseItemStack();
	
	// Functionality
	virtual FItemStack GetItemStackAtIndex_Implementation(const int Index) const override;
	
	virtual void SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack) override;

	virtual int GetContainerSize_Implementation() const override;
};
