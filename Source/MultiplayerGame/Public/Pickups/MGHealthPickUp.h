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

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "0"))
	float HealthAmount = 25.0f;

  private:
	virtual bool GivePickUpTo(APawn *PlayerPawn) override;
};
