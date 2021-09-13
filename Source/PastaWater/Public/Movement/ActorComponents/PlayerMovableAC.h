// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/MovableACInterface.h"

#include "PlayerMovableAC.generated.h"


UCLASS(Blueprintable)
class PASTAWATER_API UPlayerMovableAC : public UActorComponent, public IMovableACInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	float MouseSensitivity = 1;
	// Sets default values for this component's properties
	UPlayerMovableAC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void PerformJumpAction_Implementation() override;

	virtual void PerformMoveForwardBackward_Implementation(const float AxisValue) override;
	
	virtual void PerformMoveRightLeft_Implementation(const float AxisValue) override;

	virtual void PerformLookPitch_Implementation(const float AxisValue) override;
	
	virtual void PerformLookYaw_Implementation(const float AxisValue) override;
};
