// Multiplayer Game

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "MGChangeWeaponService.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERGAME_API UMGChangeWeaponService : public UBTService
{
	GENERATED_BODY()
  public:
	UMGChangeWeaponService();

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Service", meta = (ClampMin = "0", ClampMax = "1"))
	float Probability = 0.8f;

  private:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
