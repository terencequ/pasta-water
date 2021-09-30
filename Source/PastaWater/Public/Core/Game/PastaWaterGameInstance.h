#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Templates/SharedPointer.h"
#include "PastaWaterGameInstance.generated.h"


/**
 * Main Game Instance in Pasta Water. Can handle online sessions, and global game state.
 */
UCLASS()
class PASTAWATER_API UPastaWaterGameInstance : public UGameInstance
{
	GENERATED_BODY()

	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;
	
	TSharedPtr<class FOnlineSessionSettings> SessionSettings;
	
	UPastaWaterGameInstance(const FObjectInitializer& ObjectInitializer);
	
	/**
	 *	Function to host a game!
	 *
	 *	@param	UserId			User that started the request
	 *	@param	SessionName		Name of the Session
	 *	@param	bIsLAN			Is this is LAN Game?
	 *	@param	bIsPresence		Allow your Session to be joined by friends TODO: Research
	 *	@param	MaxNumPlayers	Number of maximum allowed players on this Session (Server)
	 */
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);
	
	/**
	 *	Function fired when a session create request has completed
	 *
	 *	@param SessionName the name of the session this callback is for
	 *	@param bWasSuccessful true if the async action completed without error, false if there was an error
	 */
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	
	/**
	 *	Function fired when a session start request has completed
	 *
	 *	@param SessionName the name of the session this callback is for
	 *	@param bWasSuccessful true if the async action completed without error, false if there was an error
	 */
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	
};
