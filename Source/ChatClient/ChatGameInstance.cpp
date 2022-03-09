// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatGameInstance.h"
#include "ChatWidget.h"
#include "ChatTemplate.h"
#include "ChatConnection.h"
#include "ChatPlayerController.h"

TWeakObjectPtr<UChatTemplate> UChatGameInstance::GetChatWidget() const
{
	return MakeWeakObjectPtr<UChatTemplate>(ChatTemplate);
}

//TWeakObjectPtr<UChatConnection> UChatGameInstance::GetChatConnection() const
//{
//	return MakeWeakObjectPtr<UChatConnection>(ChatConnection);
//}

UChatGameInstance::UChatGameInstance()
{
	static ConstructorHelpers::FClassFinder<UChatTemplate> chatTemplateClass(TEXT("/Game/UI/BPChatTemplate"));
	if (chatTemplateClass.Succeeded())
	{
		ChatTemplateClass = chatTemplateClass.Class;
		UE_LOG(LogTemp, Log, TEXT("CALL UChatGameInstance::ConstructorHelpers"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("CALL UChatGameInstance::ConstructorHelpers FAILED"));
	}
}

UChatGameInstance::~UChatGameInstance()
{

}

void UChatGameInstance::CreateChatWidget(AChatPlayerController* owner)
{
	if (ChatTemplateClass)
	{
		ChatTemplate = CreateWidget<UChatTemplate>(owner, ChatTemplateClass, TEXT("ChatWidget"));
		UE_LOG(LogTemp, Log, TEXT("CALL UChatGameInstance::Init"));
	}
}

void UChatGameInstance::CreateChatConnection()
{
	//ChatConnection = NewObject<UChatConnection>();
	//if(ChatWidget) ChatConnection->SetWidget(MakeWeakObjectPtr(ChatWidget));
}

void UChatGameInstance::Init()
{
	Super::Init();
}
