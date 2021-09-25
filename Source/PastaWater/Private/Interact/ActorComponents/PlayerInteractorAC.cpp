#include "Interact/ActorComponents/PlayerInteractorAC.h"

/**
 * Trace channel for interaction
 */
#define COLLISION_INTERACT ECC_EngineTraceChannel1

UPlayerInteractorAC::UPlayerInteractorAC()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	// Setup dependent variables.
	PlayerController = Cast<APlayerController>(GetOwner());
}


void UPlayerInteractorAC::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UPlayerInteractorAC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Raycast to see if interactable is there
	FHitResult HitResult;
	bool Success = GetWorld()->LineTraceSingleByChannel(HitResult, GetStartVector(), GetForwardVector(), COLLISION_INTERACT);
	if(Success)
	{
		
	}
}

void UPlayerInteractorAC::Interact_Implementation(const TScriptInterface<IInteractableInterface>& Interactable)
{
	Super::Interact_Implementation(Interactable);
}

FVector UPlayerInteractorAC::GetStartVector()
{
	return PlayerController->GetPawn()->GetActorLocation();
}

FVector UPlayerInteractorAC::GetForwardVector()
{
	return PlayerController->GetPawn()->GetActorForwardVector();
}