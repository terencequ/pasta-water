// Fill out your copyright notice in the Description page of Project Settings.


#include "PastaWaterCharacterBase.h"

// Sets default values
APastaWaterCharacterBase::APastaWaterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APastaWaterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APastaWaterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APastaWaterCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

