// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Player/MGPlayerState.h"

/**
 * 
 */

UE_DISABLE_OPTIMIZATION
class MULTIPLAYERGAME_API MGUtils
{
public:
	MGUtils();
	~MGUtils();

	template <typename T> static T *GetComponent(const AActor *Actor)
	{
		if (!Actor)
			return nullptr;

		const auto Component = Actor->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}

	bool static AreEnemies(AController *Controller1, AController *Controller2)
	{
		if (!Controller1 || !Controller2 || Controller1 == Controller2)
		{
			return false;		
		}
		const auto PlayerState1 = Cast<AMGPlayerState>(Controller1->PlayerState);
		const auto PlayerState2 = Cast<AMGPlayerState>(Controller2->PlayerState);

		return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
	}
}
UE_ENABLE_OPTIMIZATION

;

