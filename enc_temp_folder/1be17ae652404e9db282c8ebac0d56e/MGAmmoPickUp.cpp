// Multiplayer Game

#include "Pickups/MGAmmoPickUp.h"
#include "Components/MGHealthComponent.h"
#include "Components/MGWeaponComponent.h"
#include "MGUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickUp, All, All);

bool AMGAmmoPickUp::GivePickUpTo(APawn *PlayerPawn)
{
	const auto Health = MGUtils::GetComponent<UMGHealthComponent>(PlayerPawn);
	if (!Health || Health->IsDead())
	{
		return false;
	}

	const auto Weapon = MGUtils::GetComponent<UMGWeaponComponent>(PlayerPawn);
	if (!Weapon)
	{
		return false;
	}
	return Weapon->TryToAddAmmo(WeaponType, ClipsAmount);
}
