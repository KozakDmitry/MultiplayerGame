// Multiplayer Game


#include "MGGameModeBase.h"
#include "Player/MGBaseCharacter.h"
#include "Player/MGPlayerController.h"
#include "UI/MGGameHUD.h"
AMGGameModeBase::AMGGameModeBase()
{
	DefaultPawnClass = AMGBaseCharacter::StaticClass();
	PlayerControllerClass = AMGPlayerController::StaticClass();
	HUDClass = AMGGameHUD::StaticClass();
}
