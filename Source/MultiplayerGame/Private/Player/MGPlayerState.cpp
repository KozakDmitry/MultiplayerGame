// Multiplayer Game


#include "Player/MGPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(MGPlayerStateLog, All, All)



void AMGPlayerState::LogInfo()
{
	UE_LOG(MGPlayerStateLog, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);

}
