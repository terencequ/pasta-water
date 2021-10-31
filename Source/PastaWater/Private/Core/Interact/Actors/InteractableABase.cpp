#include "Core/Interact/Actors/InteractableABase.h"

#include "Core/Helpers/DebugHelpers.h"
#include "Core/Interact/Interfaces/InteractorInterface.h"

// Sets default values
AInteractableABase::AInteractableABase()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractableABase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AInteractableABase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AInteractableABase::Validate_OnInteract_Implementation(
	const TScriptInterface<IInteractorInterface>& InteractorInterface)
{
	return true;
}

void AInteractableABase::Server_OnInteract_Implementation(
	const TScriptInterface<IInteractorInterface>& InteractorInterface)
{
	
}

void AInteractableABase::NetMulticast_OnInteract_Implementation(
	const TScriptInterface<IInteractorInterface>& InteractorInterface)
{
	
}

