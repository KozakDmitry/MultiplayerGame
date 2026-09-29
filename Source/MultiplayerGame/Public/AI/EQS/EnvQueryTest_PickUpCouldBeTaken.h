// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickUpCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UEnvQueryTest_PickUpCouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()
  public:
	UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer &ObjInit);
	virtual void RunTest(FEnvQueryInstance &QueryInstance) const override;
};
