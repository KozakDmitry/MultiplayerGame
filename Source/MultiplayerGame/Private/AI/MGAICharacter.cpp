// Multiplayer Game


#include "AI/MGAICharacter.h"
#include "AI/MGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MGAIWeaponComponent.h"
#include "BrainComponent.h"

AMGAICharacter::AMGAICharacter(const FObjectInitializer &ObjInit): Super(ObjInit.SetDefaultSubobjectClass<UMGAIWeaponComponent>("WeaponComponent"))
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

void AMGAICharacter::OnDeath()
{
	Super::OnDeath();
	const auto MGController = Cast<AAIController>(Controller);
	if (MGController && MGController->BrainComponent)
	{
		MGController->BrainComponent->Cleanup();
	}
}
