// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Inventory/ActorComponents/InventoryACBase.h"

#include "PlayerInventoryAC.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateHotbarSelectionDelegate, const int CurrentSelectedHotbarIndex);

/**
 * @brief This actor component represents the player's inventory.
 * The player has a hotbar and a main inventory.
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

	UPROPERTY(ReplicatedUsing=OnRep_CurrentSelectedHotbarIndex)
	int CurrentSelectedHotbarIndex;
	
public:
	FUpdateHotbarSelectionDelegate UpdateHotbarSelectionDelegate;
	
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
	void OnRep_HotbarItemStacks() const;

	UFUNCTION()
	void OnRep_MouseItemStack() const;

	UFUNCTION()
	void OnRep_CurrentSelectedHotbarIndex() const;
	
	// Functionality
	virtual FItemStack GetItemStackAtIndex_Implementation(const int Index) const override;
	
	virtual void SetItemStackAtIndex_Implementation(const int Index, const FItemStack ItemStack) override;

	virtual int GetContainerSize_Implementation() const override;
	
	void SelectNextHotbarIndex();
	
	void SelectPreviousHotbarIndex();

	FItemStack GetItemStackAtSelectedHotbarIndex() const;

	int GetCurrentSelectedHotbarIndex() const;
};
