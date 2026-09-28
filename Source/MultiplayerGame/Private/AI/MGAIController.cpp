// Multiplayer Game


#include "AI/MGAIController.h"
#include "AI/MGAICharacter.h"

void AMGAIController::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);
	AMGAICharacter *MGCharacter = Cast<AMGAICharacter>(InPawn);
	if (MGCharacter)
	{
		RunBehaviorTree(MGCharacter->BehaviorTreeAsset);
	}
}
