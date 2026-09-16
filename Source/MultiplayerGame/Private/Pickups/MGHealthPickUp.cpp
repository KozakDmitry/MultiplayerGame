// Multiplayer Game


#include "Pickups/MGHealthPickUp.h"
#include "Components/MGHealthComponent.h"
#include "MGUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickUp, All, All);
bool AMGHealthPickUp::GivePickUpTo(APawn *PlayerPawn)
{
	const auto HealthComponent = MGUtils::GetComponent<UMGHealthComponent>(PlayerPawn);
	if (!HealthComponent)
	{
		return false;
	}
	return HealthComponent->TryToHeal(HealthAmount);
}
