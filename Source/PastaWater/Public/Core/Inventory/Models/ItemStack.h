// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStack.generated.h"

/**
 * Represents an instance of an item.
 * <br> This instance may have:
 * <br> - Quantity
 * <br> - Durability
 */
USTRUCT(BlueprintType)
struct PASTAWATER_API FItemStack
{
	GENERATED_BODY()

	/**
	 * Used to look up a data table.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	FString ItemId;

	/**
	 * Amount available in this item stack.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables")
	int Quantity;

	FItemStack()
	{
		this->ItemId = 0;
		this->Quantity = 0;
	}
	
	FItemStack(const FString ItemId, const int Quantity)
	{
		this->ItemId = ItemId;
		this->Quantity = Quantity;
	}

	/**
	 * @brief Check if this item stack is considered a null stack.
	 * @return True if this is a null stack (empty quantity). False otherwise.
	 */
	bool IsNull() const
	{
		return ItemId == "null" || Quantity == 0;
	}

	/**
	 * @brief Create an item stack that would considered to represent "null".
	 * @return Null item stack.
	 */
	static FItemStack Null()
	{
		return FItemStack("null", 0);
	}
};
