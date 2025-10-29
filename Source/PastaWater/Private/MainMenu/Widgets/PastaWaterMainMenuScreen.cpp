// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu/Widgets/PastaWaterMainMenuScreen.h"

#include "Core/Game/PastaWaterGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UPastaWaterMainMenuScreen::HostSession()
{
	UPastaWaterGameInstance* GameInstance = Cast<UPastaWaterGameInstance>(GetWorld()->GetGameInstance());
	if(GameInstance)
	{
		GameInstance->HostSession(4);
	}
}

void UPastaWaterMainMenuScreen::JoinSession(FString SessionID)
{
	UPastaWaterGameInstance* GameInstance = Cast<UPastaWaterGameInstance>(GetWorld()->GetGameInstance());
	if(GameInstance)
	{
		GameInstance->JoinSession(SessionID);
	}
}

void UPastaWaterMainMenuScreen::Quit()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); // Get the player controller

	// Set quit preference (Quit or Background)
	TEnumAsByte QuitPreference = EQuitPreference::Quit; 

	// Call the QuitGame function
	UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, QuitPreference, true); 
}