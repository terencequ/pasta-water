#include "Player/PlayerInteractorAC.h"

#include "DrawDebugHelpers.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Interact/Actors/ItemInteractable.h"

/**
 * Trace channel for interaction
 */
#define COLLISION_INTERACT ECollisionChannel::ECC_GameTraceChannel1

UPlayerInteractorAC::UPlayerInteractorAC()
{
	PrimaryComponentTick.bCanEverTick = true;
	CurrentInteractable = TScriptInterface<IInteractableInterface>(nullptr);
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

	FCollisionQueryParams HitQueryParams = FCollisionQueryParams();
	FHitResult HitResult;

	const FVector StartVector = GetStartVector();
	const FVector EndVector = StartVector + GetForwardVector()*InteractionRangeCentimeters;

	if(StartVector.IsZero() || EndVector.IsZero()){ return; } // Zero check
	
	const bool Success = GetWorld()->LineTraceSingleByChannel(HitResult, StartVector, EndVector, COLLISION_INTERACT, HitQueryParams);
	bool ShouldBroadcast = false;
	if (Success)
	{
		ShouldBroadcast = CurrentInteractable != HitResult.GetActor();
		CurrentInteractable = Cast<AItemInteractable>(HitResult.GetActor());
	} else
	{
		ShouldBroadcast = CurrentInteractable != nullptr;
		CurrentInteractable = nullptr;
	}

	// Broadcast CurrentInteractable change if different
	if(ShouldBroadcast)
	{
		UpdateInteractablesDelegate.Broadcast(Execute_GetValidInteractables(this));
	}
}

void UPlayerInteractorAC::Interact_Implementation()
{
	Super::Interact_Implementation();
}

TArray<TScriptInterface<IInteractableInterface>> UPlayerInteractorAC::GetValidInteractables_Implementation() const
{
	TArray<TScriptInterface<IInteractableInterface>> InteractableInterfaces;
	InteractableInterfaces.Init(TScriptInterface<IInteractableInterface>(nullptr), 1);
	InteractableInterfaces[0] = TScriptInterface<IInteractableInterface>(CurrentInteractable);
	return InteractableInterfaces;
}

void UPlayerInteractorAC::DrawDebugInteractLine()
{
	// Raycast to see if interactable is there
	if(!IsValid(GetWorld())) return;

	FCollisionQueryParams HitQueryParams = FCollisionQueryParams();
	FHitResult HitResult;

	const FVector StartVector = GetStartVector();
	const FVector EndVector = StartVector + GetForwardVector()*InteractionRangeCentimeters;

	if(StartVector.IsZero() || EndVector.IsZero()){ return; } // Zero check
	
	const bool Success = GetWorld()->LineTraceSingleByChannel(HitResult, StartVector, EndVector, COLLISION_INTERACT, HitQueryParams);
	if (Success)
	{
		DrawDebugLine(GetWorld(), StartVector, HitResult.Location, FColor::Red, false, 2.5f);
		DrawDebugBox(GetWorld(), HitResult.Location, FVector(1.5f, 1.5f, 1.5f), FColor::Red, false, 2.5f);
		DrawDebugLine(GetWorld(), HitResult.Location, EndVector, FColor::Green, false, 2.5f);
	} else
	{
		DrawDebugLine(GetWorld(), StartVector, EndVector, FColor::Red, false, 2.5f);
	}
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