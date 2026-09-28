// Multiplayer Game

#include "Components/MGAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/MGHealthComponent.h"
#include "MGUtils.h"
#include "Perception/AISense_Sight.h"

UE_DISABLE_OPTIMIZATION
AActor *UMGAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor *> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if (PercieveActors.Num() == 0)
	{
		return nullptr;
	}
	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller)
	{
		return nullptr;
	}
	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		return nullptr;
	}
	float BestDistance = UE_MAX_FLT;
	AActor *BestPawn = nullptr;
	for (const auto PerceiveActor : PercieveActors)
	{
		const auto HealthComponent = MGUtils::GetComponent<UMGHealthComponent>(PerceiveActor);
		if (HealthComponent && !HealthComponent->IsDead())
		{
			float CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PerceiveActor;
			}

		}
	}
	return BestPawn;
}
UE_ENABLE_OPTIMIZATION