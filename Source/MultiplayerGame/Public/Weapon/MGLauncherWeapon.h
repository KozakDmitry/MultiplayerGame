// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MGBaseWeapon.h"
#include "Weapon/MGProjectile.h"
#include "MGLauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AMGLauncherWeapon : public AMGBaseWeapon
{
	GENERATED_BODY()
	
	public:
	virtual void StartFire() override;

	protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	  TSubclassOf<AMGProjectile> ProjectileClass;
	virtual void MakeShot() override;
};
