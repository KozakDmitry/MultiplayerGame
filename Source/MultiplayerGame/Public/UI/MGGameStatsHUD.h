// Multiplayer Game

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGGameStatsHUD.generated.h"

class UTextBlock;
class AMGGameModeBase;

/**
 *
 */
UCLASS()
class MULTIPLAYERGAME_API UMGGameStatsHUD : public UUserWidget
{
	GENERATED_BODY()

  public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

  protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock *RoundTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock *TimeTextBlock;
	UPROPERTY(meta = (BindWidget))
	UTextBlock *KillsTextBlock;

  private:
	void OnGameDataChanged(int32 Round, int32 TotalRounds, int32 TimeLeft);
	void UpdateRound(int32 Round, int32 TotalRounds);
	void UpdateTime(int32 TimeLeft);
	void UpdateKills();

	UPROPERTY()
	AMGGameModeBase *GameModeRef;
};
