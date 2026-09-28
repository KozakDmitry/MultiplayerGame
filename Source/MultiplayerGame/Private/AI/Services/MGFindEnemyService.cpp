// Multiplayer Game

#include "AI/Services/MGFindEnemyService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MGUtils.h"
#include "Components/MGAIPerceptionComponent.h"

UE_DISABLE_OPTIMIZATION
UMGFindEnemyService::UMGFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UMGFindEnemyService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = MGUtils::GetComponent<UMGAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
UE_ENABLE_OPTIMIZATION
