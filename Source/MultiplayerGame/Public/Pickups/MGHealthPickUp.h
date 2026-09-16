// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Pickups/MGBasePickUp.h"
#include "MGHealthPickUp.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERGAME_API AMGHealthPickUp : public AMGBasePickUp
{
	GENERATED_BODY()

  private:
	virtual bool GivePickUpTo(APawn *PlayerPawn) override;
};
