// Multiplayer Game

#include "AI/Decorators/MGWeaponAmmoBTDecorator.h"
#include "MGUtils.h"
#include "AIController.h"
#include "Components/MGWeaponComponent.h"
#include "MGCoreTypes.h"
#include "Weapon/MGBaseWeapon.h"

UMGWeaponAmmoBTDecorator::UMGWeaponAmmoBTDecorator()
{
	NodeName = "Weapon Ammo";
}

bool UMGWeaponAmmoBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)
	{
		return false;
	}
	const auto WeaponComponent = MGUtils::GetComponent<UMGWeaponComponent>(Controller->GetPawn());
	if (!WeaponComponent)
	{
		return false;
	}
	FAmmoData AmmoData;
	if (!WeaponComponent->GetWeaponAmmoData(AmmoData))
	{
		return false;
	}
	if (AmmoData.Infinite || AmmoData.Clips >= RequiredClips)
	{
		return false;
	}
	return !RequiredWeapon || WeaponComponent->GetCurrentWeaponClass() == RequiredWeapon;
}
