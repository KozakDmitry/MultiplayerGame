// Multiplayer Game


#include "AI/MGAICharacter.h"
#include "AI/MGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AMGAICharacter::AMGAICharacter(const FObjectInitializer &ObjInit): Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AMGAIController::StaticClass();

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}
