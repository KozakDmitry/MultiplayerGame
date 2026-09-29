// Multiplayer Game

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"
#include "MGWeaponAmmoBTDecorator.generated.h"

class AMGBaseWeapon;

/**
 * Passes while the weapon the owning AI holds has fewer clips than RequiredClips.
 *
 * RequiredWeapon narrows the check to one weapon class, leaving it unset applies to whichever weapon
 * the bot happens to hold. A weapon with an infinite reserve never runs dry, so it never counts as a
 * shortage. Locating and walking to a pickup is left to a task, this only reports that ammo is needed.
 */
UCLASS()
class MULTIPLAYERGAME_API UMGWeaponAmmoBTDecorator : public UBTDecorator
{
	GENERATED_BODY()
  public:
	UMGWeaponAmmoBTDecorator();

  protected:
	// Weapon this check applies to, leave unset to check whatever the bot is holding
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AMGBaseWeapon> RequiredWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0"))
	int32 RequiredClips = 1;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
