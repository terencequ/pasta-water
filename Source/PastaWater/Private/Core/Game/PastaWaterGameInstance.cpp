#include "Core/Game/PastaWaterGameInstance.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"

UPastaWaterGameInstance::UPastaWaterGameInstance(const FObjectInitializer& ObjectInitializer)
{
	/** Bind function for CREATING a Session */
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(
		this, &UPastaWaterGameInstance::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(
		this, &UPastaWaterGameInstance::OnStartOnlineGameComplete);
}

bool UPastaWaterGameInstance::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN,
                                          bool bIsPresence, int32 MaxNumPlayers)
{
	// Get the Online Subsystem to work with
	IOnlineSubsystem* const OnlineSub = Online::GetSubsystem(GetWorld());

	if (OnlineSub)
	{
		// Get the Session Interface, so we can call the "CreateSession" function on it
		IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();

		if (Sessions.IsValid() && UserId.IsValid())
		{
			/* 
				Fill in all the Session Settings that we want to use.
					
				There are more with SessionSettings.Set(...);
				For example the Map or the GameMode/Type.
			*/
			SessionSettings = MakeShareable(new FOnlineSessionSettings());

			SessionSettings->bIsLANMatch = bIsLAN;
			SessionSettings->bUsesPresence = bIsPresence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;

			SessionSettings->Set(SETTING_MAPNAME, FString("TestMap"), EOnlineDataAdvertisementType::ViaOnlineService);

			// Set the delegate to the Handle of the SessionInterface
			OnCreateSessionCompleteDelegateHandle = Sessions->AddOnCreateSessionCompleteDelegate_Handle(
				OnCreateSessionCompleteDelegate);

			// Our delegate should get called when this is complete (doesn't need to be successful!)
			return Sessions->CreateSession(*UserId, SessionName, *SessionSettings);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("No OnlineSubsytem found!"));
	}

	return false;
}

void UPastaWaterGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful)
{
}

void UPastaWaterGameInstance::OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful)
{
}
