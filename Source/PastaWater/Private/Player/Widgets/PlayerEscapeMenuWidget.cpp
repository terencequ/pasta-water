// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Widgets/PlayerEscapeMenuWidget.h"

#include "Core/Game/PastaWaterGameInstance.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Windows/WindowsPlatformApplicationMisc.h"

FString UPlayerEscapeMenuWidget::GetSessionName() const
{
	// Assuming the session name is stored in the game instance
	if (GetWorld())
	{
		UPastaWaterGameInstance* GameInstance = Cast<UPastaWaterGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			return GameInstance->GetCurrentSessionName();
		}
	}
	return FString("No Session");
}

void UPlayerEscapeMenuWidget::CopySessionId()
{
	// Copy session ID to clipboard
	FPlatformApplicationMisc::ClipboardCopy(*GetSessionName());
	
	UDebugHelpers::ScreenLogInfo("Session ID copied to clipboard: " + GetSessionName());
}

void UPlayerEscapeMenuWidget::QuitToMainMenu()
{
	if (GetWorld())
	{
		UPastaWaterGameInstance* GameInstance = Cast<UPastaWaterGameInstance>(GetWorld()->GetGameInstance());
		if (GameInstance)
		{
			// Leave the session before quitting to main menu
			GameInstance->LeaveSession();

			// Open main menu level
			UGameplayStatics::OpenLevel(GetWorld(), "/Game/PastaWater/Levels/MainMenuLevel");
		}
		
	}
}

void UPlayerEscapeMenuWidget::QuitGame()
{
	if (GetWorld())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, true);
		}
	}
}

UPlayerEscapeMenuWidget* UPlayerEscapeMenuWidget::Create(const TSubclassOf<UPlayerEscapeMenuWidget>& PlayerEscapeMenuWidgetClass,
                                                         APastaWaterPlayerControllerBase* OwningPlayerController)
{
	// Create widget
	UPlayerEscapeMenuWidget* PlayerEscapeMenuWidget = CreateWidget<UPlayerEscapeMenuWidget>(
		OwningPlayerController,
		PlayerEscapeMenuWidgetClass,
		"Player Escape Menu");

	// Failure check
	if(!IsValid(PlayerEscapeMenuWidget))
	{
		UDebugHelpers::ScreenLogError("Could not initialise Player Escape Menu Widget.");
		return nullptr;
	}

	PlayerEscapeMenuWidget->SetVisibility(ESlateVisibility::Hidden);
    PlayerEscapeMenuWidget->AddToViewport(100);
	return PlayerEscapeMenuWidget;
}
