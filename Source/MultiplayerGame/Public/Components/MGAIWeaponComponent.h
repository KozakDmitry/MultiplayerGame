// Multiplayer Game

#pragma once

#include "Components/MGWeaponComponent.h"
#include "CoreMinimal.h"
#include "MGAIWeaponComponent.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERGAME_API UMGAIWeaponComponent : public UMGWeaponComponent
{
	GENERATED_BODY()

  public:
	virtual void StartFire() override;
	virtual void NextWeapon() override;
};
