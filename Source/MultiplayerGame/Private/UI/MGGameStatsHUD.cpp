// Multiplayer Game


#include "UI/MGGameStatsHUD.h"
#include "Components/TextBlock.h"
#include "MGGameModeBase.h"
#include "Player/MGPlayerState.h"

void UMGGameStatsHUD::NativeConstruct()
{
	Super::NativeConstruct();

	GameModeRef = GetWorld() ? GetWorld()->GetAuthGameMode<AMGGameModeBase>() : nullptr;
	if (GameModeRef)
	{
		GameModeRef->OnGameDataChanged.AddUObject(this, &UMGGameStatsHUD::OnGameDataChanged);
		OnGameDataChanged(GameModeRef->GetCurrentRound(), GameModeRef->GetRoundNum(), GameModeRef->GetRoundCountDown());
	}
	else
	{
		UpdateKills();
	}
}

void UMGGameStatsHUD::NativeDestruct()
{
	if (GameModeRef)
	{
		GameModeRef->OnGameDataChanged.RemoveAll(this);
		GameModeRef = nullptr;
	}
	Super::NativeDestruct();
}

void UMGGameStatsHUD::OnGameDataChanged(int32 Round, int32 TotalRounds, int32 TimeLeft)
{
	UpdateRound(Round, TotalRounds);
	UpdateTime(TimeLeft);
	UpdateKills();
}

void UMGGameStatsHUD::UpdateRound(int32 Round, int32 TotalRounds)
{
	if (!RoundTextBlock)
	{
		return;
	}
	const FString RoundString = FString::Printf(TEXT("Round: %d/%d"), Round, TotalRounds);
	RoundTextBlock->SetText(FText::FromString(RoundString));
}

void UMGGameStatsHUD::UpdateTime(int32 TimeLeft)
{
	if (!TimeTextBlock)
	{
		return;
	}
	const int32 Minutes = TimeLeft / 60;
	const int32 Seconds = TimeLeft % 60;
	const FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
	TimeTextBlock->SetText(FText::FromString(TimeString));
}

void UMGGameStatsHUD::UpdateKills()
{
	if (!KillsTextBlock)
	{
		return;
	}
	int32 Kills = 0;
	if (const auto PlayerController = GetOwningPlayer())
	{
		if (const auto PlayerState = Cast<AMGPlayerState>(PlayerController->PlayerState))
		{
			Kills = PlayerState->GetKillsNum();
		}
	}
	KillsTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Kills: %d"), Kills)));
}
