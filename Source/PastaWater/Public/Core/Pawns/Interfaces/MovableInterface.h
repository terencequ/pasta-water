#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MovableInterface.generated.h"

UINTERFACE()
class UMovableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for a movable object.
 */
class PASTAWATER_API IMovableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Actions")
	void PerformJumpAction();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Movement")
	void PerformMoveForwardBackward(const float AxisValue);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Movement")
	void PerformMoveRightLeft(const float AxisValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Looking")
	void PerformLookPitch(const float AxisValue);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Looking")
	void PerformLookYaw(const float AxisValue);
};
