#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Interact/Interfaces/InteractorInterface.h"
#include "InteractorACBase.generated.h"

/**
 * Base AC for an Interactor.
 */
UCLASS(Blueprintable)
class PASTAWATER_API UInteractorACBase : public UActorComponent, public IInteractorInterface
{
	GENERATED_BODY()

public:
	UInteractorACBase();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Interact_Implementation(const TScriptInterface<IInteractableInterface>& Interactable) override;
};
