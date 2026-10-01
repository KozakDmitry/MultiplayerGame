// Multiplayer Game

#include "MGGameModeBase.h"
#include "AIController.h"
#include "Player/MGBaseCharacter.h"
#include "Player/MGPlayerController.h"
#include "UI/MGGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogMGGameBaseMode, All, All)
AMGGameModeBase::AMGGameModeBase()
{
	DefaultPawnClass = AMGBaseCharacter::StaticClass();
	PlayerControllerClass = AMGPlayerController::StaticClass();
	HUDClass = AMGGameHUD::StaticClass();
}

void AMGGameModeBase::StartPlay()
{
	Super::StartPlay();
	SpawnBots();
	CurrentRound = 1;
	StartRound();
}

UClass *AMGGameModeBase::GetDefaultPawnClassForController_Implementation(AController *InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AMGGameModeBase::SpawnBots()
{
	if (!GetWorld())
	{
		return;
	}
	for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto MGAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(MGAIController);
	}
}

void AMGGameModeBase::StartRound()
{
	RoundCountDown = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AMGGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AMGGameModeBase::GameTimerUpdate()
{
	UE_LOG(LogMGGameBaseMode, Display, TEXT("Time: %i / Round %i/%i"), RoundCountDown, CurrentRound,GameData.RoundNum);

	
	if (--RoundCountDown == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
		if (CurrentRound + 1 <= GameData.RoundNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			UE_LOG(LogMGGameBaseMode, Display, TEXT("==== GAME OVER ===="));

		}
	}
}

void AMGGameModeBase::ResetPlayers()
{
	if (!GetWorld())
	{
		return;
	}
	for (auto it = GetWorld()->GetControllerIterator(); it; ++it)
	{
		ResetOnePlayer(it->Get());
	}
}

void AMGGameModeBase::ResetOnePlayer(AController *Controller)
{
	if (Controller && Controller->GetPawn())
	{
		Controller->GetPawn()->Reset();
	}
	RestartPlayer(Controller);
}
