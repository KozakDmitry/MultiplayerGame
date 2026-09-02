// Multiplayer Game


#include "MGGameModeBase.h"
#include "Player/MGBaseCharacter.h"
#include "Player/MGPlayerController.h"

AMGGameModeBase::AMGGameModeBase()
{
	DefaultPawnClass = AMGBaseCharacter::StaticClass();
	PlayerControllerClass = AMGPlayerController::StaticClass();
}
