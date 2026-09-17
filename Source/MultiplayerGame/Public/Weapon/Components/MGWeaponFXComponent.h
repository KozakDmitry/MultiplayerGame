// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MGWeaponFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERGAME_API UMGWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMGWeaponFXComponent();

	void PlayImpactFX(const FHitResult &Hit);

	protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	  UNiagaraSystem *Effect;
		
};
