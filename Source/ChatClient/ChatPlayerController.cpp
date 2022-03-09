// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatPlayerController.h"
#include "ChatConnection.h"
#include "ChatGameInstance.h"
#include "ChatWidget.h"
#include "ChatTemplate.h"

AChatPlayerController::AChatPlayerController()
{
}

AChatPlayerController::~AChatPlayerController()
{

}

// Called when the game starts or when spawned
void AChatPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UChatGameInstance* gameInstance = Cast<UChatGameInstance>(GetGameInstance());
	gameInstance->CreateChatWidget(this);
	gameInstance->CreateChatConnection();
	ChatTemplate = gameInstance->GetChatWidget();
	//ChatConnection = gameInstance->GetChatConnection();
	if (ChatTemplate.IsValid())
	{
		ChatTemplate->AddToViewport();
		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());
	}
}

void AChatPlayerController::PlayerTick(float deltaTime)
{
	//if (ChatConnection.IsValid()) ChatConnection->Process();
}


