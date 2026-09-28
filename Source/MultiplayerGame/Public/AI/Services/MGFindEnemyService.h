// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MGFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UMGFindEnemyService : public UBTService
{
	GENERATED_BODY()
  public:
	UMGFindEnemyService();

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
