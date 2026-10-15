// Multiplayer Game

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "MGRespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MULTIPLAYERGAME_API UMGRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	UMGRespawnComponent();
	void Respawn(int32 TimeRespawn);

  private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;
	void RespawnTimerUpdate();
	// Called every frame
};
