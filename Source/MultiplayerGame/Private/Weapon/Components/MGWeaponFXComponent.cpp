// Multiplayer Game

#include "Weapon/Components/MGWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UMGWeaponFXComponent::UMGWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
	// features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UMGWeaponFXComponent::PlayImpactFX(const FHitResult &Hit)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}
