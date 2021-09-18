#include "Interact/Actors/InteractableABase.h"
#include "Helpers/DebugHelpers.h"

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

void AInteractableABase::OnInteract_Implementation(const TScriptInterface<IInteractorInterface>& Interactable)
{
	UDebugHelpers::ScreenLogInfo(GetName()+"was interacted with by something.");
}

