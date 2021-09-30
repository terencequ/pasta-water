#include "Player/PlayerInteractorAC.h"

#include "DrawDebugHelpers.h"
#include "Core/Helpers/DebugHelpers.h"

/**
 * Trace channel for interaction
 */
#define COLLISION_INTERACT ECC_EngineTraceChannel1

UPlayerInteractorAC::UPlayerInteractorAC()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UPlayerInteractorAC::BeginPlay()
{
	Super::BeginPlay();

	// Setup dependent variables.
	PlayerController = Cast<APlayerController>(GetOwner());
}


// Called every frame
void UPlayerInteractorAC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Raycast to see if interactable is there
	if(!IsValid(GetWorld())) return;

	FHitResult HitResult;

	const FVector StartVector = GetStartVector();
	const FVector EndVector = StartVector + GetForwardVector()*InteractionRangeCentimeters;

	if(StartVector.IsZero() || EndVector.IsZero()){ return; } // Zero check
	
	const bool Success = GetWorld()->LineTraceSingleByChannel(HitResult, StartVector, EndVector, COLLISION_INTERACT);
	if(Success)
	{
		UDebugHelpers::ScreenLogInfo("Can see interactable");
	}
	DrawDebugLine(GetWorld(), StartVector, EndVector, Success ? FColor::Green : FColor::Red, false, -1.0f);
}

void UPlayerInteractorAC::Interact_Implementation(const TScriptInterface<IInteractableInterface>& Interactable)
{
	Super::Interact_Implementation(Interactable);
}

FVector UPlayerInteractorAC::GetStartVector()
{
	if(!IsValid(PlayerController)) return FVector::ZeroVector;
	if(!IsValid(PlayerController->PlayerCameraManager)) return FVector::ZeroVector;
	return PlayerController->PlayerCameraManager->GetCameraLocation();
}

FVector UPlayerInteractorAC::GetForwardVector()
{
	if(!IsValid(PlayerController)) return FVector::ZeroVector;
	if(!IsValid(PlayerController->PlayerCameraManager)) return FVector::ZeroVector;

	return PlayerController->PlayerCameraManager->GetActorForwardVector();
}