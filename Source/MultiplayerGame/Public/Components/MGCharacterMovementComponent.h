// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MGCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class MULTIPLAYERGAME_API UMGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10"))
	float runMultiplier = 2.0f;
	virtual float GetMaxSpeed() const override;
};
