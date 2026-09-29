// Multiplayer Game

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "MGFireService.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERGAME_API UMGFireService : public UBTService
{
	GENERATED_BODY()
  public:
	UMGFireService();
  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
