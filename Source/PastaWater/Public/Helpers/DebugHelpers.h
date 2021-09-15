// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DebugHelpers.generated.h"

/**
 * 
 */
UCLASS()
class PASTAWATER_API UDebugHelpers : public UObject
{
	GENERATED_BODY()

public:
	static void ScreenLogInfo(FString Text);
	
	static void ScreenLogWarning(FString Text);
	
	static void ScreenLogError(FString Text);
};
