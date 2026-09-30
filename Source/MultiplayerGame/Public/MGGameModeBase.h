// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MGCoreTypes.h"
#include "MGGameModeBase.generated.h"

/**
 *
 */
class AAIController;

UCLASS()
class MULTIPLAYERGAME_API AMGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

  public:
	AMGGameModeBase();

	virtual void StartPlay() override;
  protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

  private:
	void SpawnBots();

};
