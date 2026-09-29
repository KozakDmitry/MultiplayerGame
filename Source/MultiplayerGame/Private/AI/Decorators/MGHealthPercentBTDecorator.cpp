// Multiplayer Game

#include "AI/Decorators/MGHealthPercentBTDecorator.h"
#include "MGUtils.h"
#include "AIController.h"
#include "Components/MGHealthComponent.h"

UMGHealthPercentBTDecorator::UMGHealthPercentBTDecorator()
{
	NodeName = "Health Percent";
}

bool UMGHealthPercentBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)
	{
		return false;
	}
	const auto HealthComponent = MGUtils::GetComponent<UMGHealthComponent>(Controller->GetPawn());
	if (!HealthComponent || HealthComponent->IsDead())
	{
		return false;
	}

	return HealthComponent->GetHealthPersent() <= HealthPercent;
}
