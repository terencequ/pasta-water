#pragma once

#include "CoreMinimal.h"
#include "Core/Interact/Actors/InteractableABase.h"
#include "ItemInteractable.generated.h"

UCLASS()
class PASTAWATER_API AItemInteractable : public AInteractableABase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemId;
	
	AItemInteractable();

	virtual void OnInteract_Implementation(const TScriptInterface<IInteractorInterface>& Interactable) override;
};
