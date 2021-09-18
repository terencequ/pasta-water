// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInventoryAC.h"
#include "Components/ActorComponent.h"
#include "Inventory/Widgets/PlayerInventoryWidget.h"
#include "PlayerInventoryDisplayAC.generated.h"


UCLASS(Blueprintable)
class PASTAWATER_API UPlayerInventoryDisplayAC : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	APastaWaterPlayerControllerBase* PlayerController;

	UPROPERTY(BlueprintReadWrite)
	UPlayerInventoryAC* PlayerInventoryAC;
	
	UPROPERTY(BlueprintReadWrite)
	UPlayerInventoryWidget* PlayerInventoryWidget;

	/**
	 * Populate this in the editor. Determines the class of the Player Inventory.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPlayerInventoryWidget> PlayerInventoryWidgetClass;
	
	// Sets default values for this component's properties
	UPlayerInventoryDisplayAC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Toggles Player Inventory UI.
	 */
	UFUNCTION(BlueprintCallable, Category="Toggle")
	void ToggleInventory();
};
