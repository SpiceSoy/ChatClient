//=================================================================================================
// @file ChatGameInstance.cpp
//
// @brief 채팅 위젯, 채팅 커넥션 클래스 인스턴스를 보유하기 위한 게임 인스턴스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "ChatGameInstance.h"
#include "ChatConnection.h"
#include "ChatPlayerController.h"
#include "Widget/ChatTemplate.h"


TWeakObjectPtr<UChatTemplate> UChatGameInstance::GetChatWidget() const
{
	return MakeWeakObjectPtr<UChatTemplate>( ChatTemplate );
}

TWeakObjectPtr<UChatConnection> UChatGameInstance::GetChatConnection() const
{
	return MakeWeakObjectPtr<UChatConnection>( ChatConnection );
}

UChatGameInstance::UChatGameInstance()
{
	static ConstructorHelpers::FClassFinder<UChatTemplate> chatTemplateClass( TEXT( "/Game/UI/BPChatTemplate" ) );
	if( chatTemplateClass.Succeeded() )
	{
		ChatTemplateClass = chatTemplateClass.Class;
		UE_LOG( LogTemp, Log, TEXT( "CALL UChatGameInstance::ConstructorHelpers" ) );
	}
	else
	{
		UE_LOG( LogTemp, Log, TEXT( "CALL UChatGameInstance::ConstructorHelpers FAILED" ) );
	}
}

UChatGameInstance::~UChatGameInstance()
{

}

void UChatGameInstance::CreateChatWidget( AChatPlayerController* owner )
{
	if( ChatTemplateClass )
	{
		ChatTemplate = CreateWidget<UChatTemplate>( owner, ChatTemplateClass, TEXT( "ChatWidget" ) );
		UE_LOG( LogTemp, Log, TEXT( "CALL UChatGameInstance::Init" ) );
	}
}

void UChatGameInstance::CreateChatConnection()
{
	ChatConnection = NewObject<UChatConnection>();
	if( ChatTemplate ) ChatConnection->SetChatUi( MakeWeakObjectPtr( ChatTemplate ) );
}

void UChatGameInstance::Init()
{
	Super::Init();
}
