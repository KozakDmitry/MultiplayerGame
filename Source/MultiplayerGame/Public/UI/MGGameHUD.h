// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MGGameHUD.generated.h"

/**
 * 
 */


class UMGPlayerHUDWidget;

UCLASS()
class MULTIPLAYERGAME_API AMGGameHUD : public AHUD
{
	GENERATED_BODY()
  public:
	virtual void DrawHUD() override;

	void DrawHP();
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetPlayerWidget(UMGPlayerHUDWidget *widget);
	UFUNCTION(BlueprintCallable, Category = "UI")
	UMGPlayerHUDWidget *GetPlayerHUDWidget() const { return PlayerHUDWidget; }


  private:
	UPROPERTY()
	UMGPlayerHUDWidget *PlayerHUDWidget;
	void DrawCrosshair();
};
