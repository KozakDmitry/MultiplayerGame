// Multiplayer Game

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "MGAIController.generated.h"

/**
 *
 */

class UMGAIPerceptionComponent;

UCLASS()
class MULTIPLAYERGAME_API AMGAIController : public AAIController
{
	GENERATED_BODY()
  public:
	AMGAIController();

  protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UMGAIPerceptionComponent *MGAIPerceptionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName FocusOnKeyName = "EnemyActor";
	virtual void OnPossess(APawn *InPawn) override;
	virtual void Tick(float DeltaTime) override;

  private:
	AActor *GetFocusOnActor() const;
};
