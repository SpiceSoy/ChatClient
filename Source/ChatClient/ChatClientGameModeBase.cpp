// Copyright Epic Games, Inc. All Rights Reserved.


#include "ChatClientGameModeBase.h"
#include "ChatPlayerController.h"

AChatClientGameModeBase::AChatClientGameModeBase()
{
	PlayerControllerClass = AChatPlayerController::StaticClass();
}
