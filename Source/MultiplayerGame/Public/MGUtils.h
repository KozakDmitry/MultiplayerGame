// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * 
 */
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
};
