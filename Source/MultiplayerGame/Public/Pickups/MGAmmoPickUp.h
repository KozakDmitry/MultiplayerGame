// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Pickups/MGBasePickUp.h"
#include "MGAmmoPickUp.generated.h"

/**
 *
 */
class AMGBaseWeapon;

UCLASS()
class MULTIPLAYERGAME_API AMGAmmoPickUp : public AMGBasePickUp
{
	GENERATED_BODY()

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
	int32 ClipsAmount = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TSubclassOf<AMGBaseWeapon> WeaponType;

  private:
	virtual bool GivePickUpTo(APawn *PlayerPawn) override;
};
