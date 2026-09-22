// Multiplayer Game

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MGCoreTypes.h"
#include "MGWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MULTIPLAYERGAME_API UMGWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	UMGWeaponFXComponent();

	void PlayImpactFX(const FHitResult &Hit);

  protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TMap<UPhysicalMaterial *, FImpactData> ImpactDataMap;
};
