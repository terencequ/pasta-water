#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/Interact/Interfaces/InteractorInterface.h"
#include "InteractorACBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateInteractablesDelegate, const TArray<TScriptInterface<IInteractableInterface>>);

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

	virtual TArray<TScriptInterface<IInteractableInterface>> GetValidInteractables_Implementation() const override;
	
	UFUNCTION(Client, Reliable)
	virtual void Interact_Implementation() override;

	FUpdateInteractablesDelegate UpdateInteractablesDelegate;

protected:
	UFUNCTION()
	bool Validate_Interact(UObject*  InteractableObject);

	UFUNCTION(Server, Reliable)
	void Server_Interact(UObject* InteractableInterface);

	UFUNCTION(NetMulticast, Reliable)
	void NetMulticast_Interact(UObject* InteractableInterface);
};
