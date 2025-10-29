#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
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

public:
	virtual void Init() override;
	
	UFUNCTION(BlueprintCallable)
	FString GetCurrentSessionName();
	
	UFUNCTION(BlueprintCallable)
	void HostSession(int32 MaxPlayers);

	UFUNCTION(BlueprintCallable)
	void JoinSession(FString SessionJoinCode);

	UFUNCTION(BlueprintCallable)
	void LeaveSession();

private:
	TWeakPtr<IOnlineSession> SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	FString CurrentSessionJoinCode;

	void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful) const;
	void OnFindSessionsComplete(bool bWasSuccessful);
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result) const;
};
