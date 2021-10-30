#include "Core/Game/PastaWaterGameState.h"

#include "Core/Helpers/DebugHelpers.h"

FItem* APastaWaterGameState::FindItem(int32 ItemId) const
{
	for (FName ItemIdName : ItemDefinitions->GetRowNames())
	{
		if(ItemIdName.GetNumber() == ItemId)
		{
			return ItemDefinitions->FindRow<FItem>(ItemIdName, "");
		}
	}
	return nullptr;
}

APastaWaterGameState* APastaWaterGameState::GetGameState(const UObject* Object)
{
	const UWorld* World = Object->GetWorld();
	if(!IsValid(World))
	{
		UDebugHelpers::ScreenLogError("Cannot find world!");
		return nullptr;
	}
	AGameStateBase* GameStateBase = World->GetGameState();
	if(!IsValid(GameStateBase))
	{
		UDebugHelpers::ScreenLogError("Cannot find game state!");
		return nullptr;
	}
	APastaWaterGameState* PastaWaterGameState = Cast<APastaWaterGameState>(GameStateBase);
	if(!IsValid(PastaWaterGameState))
	{
		UDebugHelpers::ScreenLogError("Cannot cast GameState to PastaWaterGameState!");
		return nullptr;
	}
	return PastaWaterGameState;
}
