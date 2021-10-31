#include "Core/Game/PastaWaterGameState.h"

#include "Core/Helpers/DebugHelpers.h"

FItem* APastaWaterGameState::FindItem(int32 ItemId) const
{
	FString ContextString;
	TArray<FName> RowNames = ItemDefinitions->GetRowNames();
	for (const auto& name : RowNames )
	{
		FItem* Row = ItemDefinitions->FindRow<FItem>(name, ContextString);
		if (Row->Id == ItemId && Row)
		{
			return Row;
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
