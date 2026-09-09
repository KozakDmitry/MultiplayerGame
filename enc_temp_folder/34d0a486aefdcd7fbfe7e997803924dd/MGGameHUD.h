// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MGGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AMGGameHUD : public AHUD
{
	GENERATED_BODY()
  public:
	virtual void DrawHUD() override;

  private:
	void DrawCrosshair();
};
