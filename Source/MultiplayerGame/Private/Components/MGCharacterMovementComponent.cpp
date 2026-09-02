// Multiplayer Game

#include "Components/MGCharacterMovementComponent.h"
#include "Player/MGBaseCharacter.h"

float UMGCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const AMGBaseCharacter *Player = Cast<AMGBaseCharacter>(GetPawnOwner());
	return (Player && Player->IsRunning()) ? MaxSpeed * runMultiplier : MaxSpeed;
}
