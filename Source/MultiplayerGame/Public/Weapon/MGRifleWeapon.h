// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MGBaseWeapon.h"
#include "MGRifleWeapon.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERGAME_API AMGRifleWeapon : public AMGBaseWeapon
{
	GENERATED_BODY()

  public:
	virtual void StartFire() override;
	virtual void StopFire() override;

  protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TimeBetweenShots = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float BulletSpread = 1.5f;

	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector &TraceStart, FVector &TraceEnd) const override;


  private:
	FTimerHandle ShotTimerHandle;
};
