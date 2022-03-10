//=================================================================================================
// @file ChatPlayerController.h
//
// @brief 커넥션 생성 및 위젯 생성, 커넥션의 틱 함수를 부르기 위한 플레이어 컨트롤러 클래스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "ChatPlayerController.h"
#include "ChatConnection.h"
#include "ChatGameInstance.h"
#include "Widget/ChatTemplate.h"

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
	UChatGameInstance* gameInstance = Cast<UChatGameInstance>( GetGameInstance() );
	gameInstance->CreateChatWidget( this );
	gameInstance->CreateChatConnection();
	ChatTemplate = gameInstance->GetChatWidget();
	ChatConnection = gameInstance->GetChatConnection();
	if( ChatTemplate.IsValid() )
	{
		ChatTemplate->AddToViewport();
		SetShowMouseCursor( true );
		SetInputMode( FInputModeUIOnly() );
	}
}

void AChatPlayerController::PlayerTick( float deltaTime )
{
	if( ChatConnection.IsValid() ) ChatConnection->Process();
}


