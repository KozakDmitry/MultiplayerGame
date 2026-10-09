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
	

  private:
	int TeamID;
	FLinearColor TeamColor;
};
