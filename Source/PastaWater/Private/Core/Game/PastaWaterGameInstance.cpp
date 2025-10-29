#include "Core/Game/PastaWaterGameInstance.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Kismet/GameplayStatics.h"

void UPastaWaterGameInstance::Init()
{
    Super::Init();
    IOnlineSubsystem* Subsystem = Online::GetSubsystem(GetWorld());
    if (Subsystem)
    {
        SessionInterface = Subsystem->GetSessionInterface();
    }

    // Invite accepted logic
    if (!Subsystem)
    {
        return;
    }
    if (!SessionInterface.IsValid()) return;
    TSharedPtr<IOnlineSession> Session = SessionInterface.Pin();
    if (Session.IsValid())
    {
        Session->AddOnSessionUserInviteAcceptedDelegate_Handle(FOnSessionUserInviteAcceptedDelegate::CreateUObject(this, &UPastaWaterGameInstance::OnInviteAccepted));
    }
}

FString UPastaWaterGameInstance::GetCurrentSessionName()
{
    return CurrentSessionJoinCode;
}

void UPastaWaterGameInstance::HostSession(int32 MaxPlayers)
{
    if (!SessionInterface.IsValid()) return;
    TSharedPtr<IOnlineSession> Session = SessionInterface.Pin();
    
    // Bind delegate
    Session->OnCreateSessionCompleteDelegates.AddUObject(this, &UPastaWaterGameInstance::OnCreateSessionComplete);

    FOnlineSessionSettings Settings;
    Settings.bIsLANMatch = true; // true for local testing
    Settings.NumPublicConnections = MaxPlayers;
    Settings.bShouldAdvertise = true;
    Settings.bUsesPresence = true;
    Settings.bAllowJoinInProgress = true;
    Settings.bAllowJoinViaPresence = true; // 🔥 important for friend join
    Settings.bAllowJoinViaPresenceFriendsOnly = false;
    Settings.bUseLobbiesIfAvailable = true; // Steam lobbies

    // Generate a unique session name and cache it
    FName SessionName = FName(FGuid::NewGuid().ToString());
    CurrentSessionJoinCode = SessionName.ToString();
    
    Settings.Set(FName("JOINCODE"), CurrentSessionJoinCode, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
    
    // Create the session
    Session->CreateSession(0, NAME_GameSession, Settings);
}


void UPastaWaterGameInstance::OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) const
{
    if (bWasSuccessful)
    {
        UGameplayStatics::OpenLevel(GetWorld(), "/Game/PastaWater/Levels/GameLevel", true, "listen");
    }
    else
    {
        UDebugHelpers::ScreenLogWarning("Failed to create session");
    }
}


void UPastaWaterGameInstance::JoinSession(FString SessionJoinCode)
{
    CurrentSessionJoinCode = SessionJoinCode;
    
    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    SessionSearch->MaxSearchResults = 20;
    SessionSearch->bIsLanQuery = false;
    SessionSearch->QuerySettings.Set(FName("JOINCODE"), SessionJoinCode, EOnlineComparisonOp::Equals);
    
    if (!SessionInterface.IsValid()) return;
    TSharedPtr<IOnlineSession> Session = SessionInterface.Pin();

    // Try find sessions
    Session->OnFindSessionsCompleteDelegates.AddUObject(this, &UPastaWaterGameInstance::OnFindSessionsComplete);

    // Start searching for sessions
    Session->FindSessions(0, SessionSearch.ToSharedRef());

}

void UPastaWaterGameInstance::LeaveSession()
{
    if (!SessionInterface.IsValid()) return;
    TSharedPtr<IOnlineSession> Session = SessionInterface.Pin();
    Session->DestroySession(NAME_GameSession);
}

void UPastaWaterGameInstance::OnFindSessionsComplete(bool bWasSuccessful)
{
    if (!SessionInterface.IsValid()) return;
    TSharedPtr<IOnlineSession> Session = SessionInterface.Pin();
    
    if (!bWasSuccessful || !SessionSearch.IsValid() || SessionSearch->SearchResults.Num() == 0)
    {
        UDebugHelpers::ScreenLogWarning("No sessions found.");
        return;
    }

    for (const FOnlineSessionSearchResult& Result : SessionSearch->SearchResults)
    {
        FString FoundCode;
        if (Result.Session.SessionSettings.Get(FName("JOINCODE"), FoundCode))
        {
            if (FoundCode.Equals(CurrentSessionJoinCode, ESearchCase::IgnoreCase))
            {
                UDebugHelpers::ScreenLogInfo("Found session with join code: "+FoundCode);

                // Bind join delegate
                Session->OnJoinSessionCompleteDelegates.AddUObject(this, &UPastaWaterGameInstance::OnJoinSessionComplete);

                // Join the session
                Session->JoinSession(0, NAME_GameSession, Result);
                return;
            }
        }
    }

    UDebugHelpers::ScreenLogError("Session with join code " + CurrentSessionJoinCode + " not found.");
}


void UPastaWaterGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) const
{
    if (!SessionInterface.IsValid()) return;
    TSharedPtr<IOnlineSession> Session = SessionInterface.Pin();

    FString ConnectString;
    if (Session->GetResolvedConnectString(SessionName, ConnectString))
    {
        APlayerController* PC = GetFirstLocalPlayerController();
        if (PC)
        {
            PC->ClientTravel(ConnectString, TRAVEL_Absolute);
            UDebugHelpers::ScreenLogInfo("Joined session "+ CurrentSessionJoinCode);
        }
    }
}

void UPastaWaterGameInstance::OnInviteAccepted(const bool bWasSuccessful, const int32 ControllerId,
    TSharedPtr<const FUniqueNetId> UserId, const FOnlineSessionSearchResult& InviteResult) const
{
    if (!SessionInterface.IsValid()) return;
    TSharedPtr<IOnlineSession> Session = SessionInterface.Pin();
    
    if (bWasSuccessful && InviteResult.IsValid())
    {
        if (Session.IsValid())
        {
            // Join the session
            Session->JoinSession(ControllerId, NAME_GameSession, InviteResult);
        }
    }
}
