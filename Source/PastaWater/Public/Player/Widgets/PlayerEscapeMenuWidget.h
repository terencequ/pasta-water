// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Core/Game/PastaWaterPlayerControllerBase.h"
#include "PlayerEscapeMenuWidget.generated.h"

/**
 * The escape menu widget for the player.
 */
UCLASS()
class PASTAWATER_API UPlayerEscapeMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/**
	 * Get the multiplayer session name.
	 */
	UFUNCTION(BlueprintCallable)
	FString GetSessionName() const;

	UFUNCTION(BlueprintCallable)
	void CopySessionId();

	UFUNCTION(BlueprintCallable)
	void QuitToMainMenu();
	
	UFUNCTION(BlueprintCallable)
	void QuitGame();
	
	UFUNCTION(BlueprintCallable)
	static UPlayerEscapeMenuWidget* Create(const TSubclassOf<UPlayerEscapeMenuWidget>& PlayerEscapeMenuWidgetClass,
	                                       APastaWaterPlayerControllerBase* OwningPlayerController);
};
