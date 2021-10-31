#include "Core/Interact/ActorComponents/InteractorACBase.h"
#include "Core/Helpers/DebugHelpers.h"
#include "Core/Interact/Interfaces/InteractableInterface.h"

// Sets default values for this component's properties
UInteractorACBase::UInteractorACBase()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInteractorACBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UInteractorACBase::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

TArray<TScriptInterface<IInteractableInterface>> UInteractorACBase::GetValidInteractables_Implementation() const
{
	TArray<TScriptInterface<IInteractableInterface>> InteractableInterfaces;
	InteractableInterfaces.Init(TScriptInterface<IInteractableInterface>(nullptr), 0);
	return InteractableInterfaces;
}

void UInteractorACBase::Interact_Implementation_Implementation()
{
	const TArray<TScriptInterface<IInteractableInterface>> InteractableInterfaces = Execute_GetValidInteractables(this);
	for(int i = 0; i < InteractableInterfaces.Num(); i++)
	{
		const TScriptInterface<IInteractableInterface> InteractableInterface = InteractableInterfaces[i];
		if(IsValid(InteractableInterface.GetObject()))
		{
			Server_Interact(InteractableInterface.GetObject());
		}
	}
}

bool UInteractorACBase::Validate_Interact(UObject* InteractableObject)
{
	IInteractableInterface* InteractableInterface = Cast<IInteractableInterface>(InteractableObject);
	if(!InteractableInterface){ return false; }
	
	bool valid = IInteractableInterface::Execute_Validate_OnInteract(InteractableObject, this);
	if(!valid)
	{
		return false;
	}

	return true;
}

void UInteractorACBase::Server_Interact_Implementation(UObject* InteractableObject)
{
	IInteractableInterface* InteractableInterface = Cast<IInteractableInterface>(InteractableObject);
	if(!InteractableInterface){ return; }
	if(!Validate_Interact(InteractableObject)){ return; }
	if(!IsValid(InteractableObject)){ return; }

	IInteractableInterface::Execute_OnInteract(InteractableObject, this);
	NetMulticast_Interact(InteractableObject);
}

void UInteractorACBase::NetMulticast_Interact_Implementation(UObject* InteractableObject)
{
	IInteractableInterface* InteractableInterface = Cast<IInteractableInterface>(InteractableObject);
	if(!InteractableInterface){ return; }
	IInteractableInterface::Execute_OnInteract(InteractableObject, this);
}
