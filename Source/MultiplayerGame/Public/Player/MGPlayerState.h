// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MGPlayerState.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERGAME_API AMGPlayerState : public APlayerState
{
	GENERATED_BODY()

  public:
	void SetTeamID(int32 ID)
	{
		TeamID = ID;
	}
	int32 GetTeamID() const
	{
		return TeamID;
	}

	void SetTeamColor(FLinearColor color)
	{
		TeamColor = color;
	}
	FLinearColor GetTeamColor() const
	{
		return TeamColor;
	}

	void AddKill()
	{
		++KillsNum;
	}
	int32 GetKillsNum() const
	{
		return KillsNum;
	}
	void AddDeath()
	{
		++DeathsNum;
	}
	int32 GetDeathsNum() const
	{
		return DeathsNum;
	}

	void LogInfo();

  private:
	int TeamID;
	FLinearColor TeamColor;

	int32 KillsNum = 0;
	int32 DeathsNum = 0;
};
