// Multiplayer Game

#include "MGGameModeBase.h"
#include "Components/MGRespawnComponent.h"

UMGRespawnComponent::UMGRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMGRespawnComponent::Respawn(int32 TimeRespawn)
{
	if (!GetWorld())
	{
		return;
	}
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UMGRespawnComponent::RespawnTimerUpdate, 1.0f,
										   true);
}

void UMGRespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		if (!GetWorld())
		{
			return;
		}
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<AMGGameModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode)
		{
			return;
		}

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	}
}


