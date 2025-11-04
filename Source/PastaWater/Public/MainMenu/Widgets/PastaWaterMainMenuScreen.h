// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PastaWaterMainMenuScreen.generated.h"

/**
 * Widget blueprint base class for the main menu screen.
 */
UCLASS()
class PASTAWATER_API UPastaWaterMainMenuScreen : public UUserWidget
{
	GENERATED_BODY()

	/**
	 * Begin hosting a multiplayer session.
	 */
	UFUNCTION(BlueprintCallable)
	void HostSession();

	/**
	 * Begin joining a multiplayer session.
	 */
	UFUNCTION(BlueprintCallable)
	void JoinSession(FString SessionID);

	/**
	 * Quit the game application.
	 */
	UFUNCTION(BlueprintCallable)
	void Quit();
};
