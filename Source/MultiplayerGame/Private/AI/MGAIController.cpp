// Multiplayer Game


#include "AI/MGAIController.h"
#include "AI/MGAICharacter.h"
#include "Components/MGAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMGAIController::AMGAIController()
{
	MGAIPerceptionComponent = CreateDefaultSubobject<UMGAIPerceptionComponent>("MGPerceptionComponent");
	SetPerceptionComponent(*MGAIPerceptionComponent);
}

void AMGAIController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);
	AMGAICharacter *MGCharacter = Cast<AMGAICharacter>(InPawn);
	if (MGCharacter)
	{
		RunBehaviorTree(MGCharacter->BehaviorTreeAsset);
	}
}

void AMGAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto AimActor = MGAIPerceptionComponent->GetClosestEnemy();
	SetFocus(AimActor);
}

AActor *AMGAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent())
	{
		return nullptr;
	}
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
