// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Helpers/DebugHelpers.h"

void UDebugHelpers::ScreenLogInfo(const FString Text)
{
	const FString LogContent = FDateTime::Now().ToString()+": (INFO): "+Text;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, LogContent);
	}
	UE_LOG(LogTemp, Display, TEXT("%s"), *LogContent);
}

void UDebugHelpers::ScreenLogWarning(const FString Text)
{
	const FString LogContent = FDateTime::Now().ToString()+": (WARNING): "+Text;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, LogContent);
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *LogContent);
}

void UDebugHelpers::ScreenLogError(const FString Text)
{
	const FString LogContent = FDateTime::Now().ToString()+": (ERROR): "+Text;
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, LogContent);
	}
	UE_LOG(LogTemp, Error, TEXT("%s"), *LogContent);
}
