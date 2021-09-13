// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Movement/ActorComponents/PlayerMovableAC.h"

#include "PastaWaterCharacterBase.generated.h"

UCLASS()
class PASTAWATER_API APastaWaterCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Actor Components")
	UPlayerMovableAC* PlayerMovableAC;
	
	// Sets default values for this character's properties
	APastaWaterCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
