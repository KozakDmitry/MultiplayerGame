// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "MGAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UMGAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
  public:
	AActor *GetClosestEnemy() const;
	
};
