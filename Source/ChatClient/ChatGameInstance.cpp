// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatGameInstance.h"
#include "ChatWidget.h"
#include "ChatPlayerController.h"

TWeakObjectPtr<UChatWidget> UChatGameInstance::GetChatWidget() const
{
	return MakeWeakObjectPtr<UChatWidget>(ChatWidget);
}

UChatGameInstance::UChatGameInstance()
{
	static ConstructorHelpers::FClassFinder<UChatWidget> chatWidgetClass(TEXT("/Game/UI/BPChatWidget"));
	if (chatWidgetClass.Succeeded())
	{
		ChatWidgetClass = chatWidgetClass.Class;
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
	if (ChatWidgetClass)
	{
		ChatWidget = CreateWidget<UChatWidget>(owner, ChatWidgetClass, TEXT("ChatWidget"));
		UE_LOG(LogTemp, Log, TEXT("CALL UChatGameInstance::Init"));
	}
}

void UChatGameInstance::Init()
{
	Super::Init();
}
