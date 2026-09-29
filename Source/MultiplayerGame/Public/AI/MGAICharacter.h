// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Player/MGBaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "MGAICharacter.generated.h"

/**
 * 
 */

UCLASS()
class MULTIPLAYERGAME_API AMGAICharacter : public AMGBaseCharacter
{
	GENERATED_BODY()
  public:
	AMGAICharacter(const FObjectInitializer &ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset = nullptr;

  protected:
	virtual void OnDeath() override;
};
