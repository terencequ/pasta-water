#pragma once

#include "CoreMinimal.h"
#include "Core/Interact/ActorComponents/InteractorACBase.h"
#include "PlayerInteractorAC.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PASTAWATER_API UPlayerInteractorAC : public UInteractorACBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int InteractionRangeCentimeters = 500;
	
	UPROPERTY(BlueprintReadWrite)
	APlayerController* PlayerController;

	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<IInteractableInterface> CurrentInteractable;
	
	// Sets default values for this component's properties
	UPlayerInteractorAC();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void Interact_Implementation(const TScriptInterface<IInteractableInterface>& Interactable) override;
	
	virtual TArray<TScriptInterface<IInteractableInterface>> GetValidInteractables_Implementation() const override;
	
	void DrawDebugInteractLine();
	
	FVector GetStartVector();

	FVector GetForwardVector();
};
