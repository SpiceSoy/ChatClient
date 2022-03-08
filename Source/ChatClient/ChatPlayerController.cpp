// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatPlayerController.h"
#include "ChatConnection.h"
#include "ChatGameInstance.h"
#include "ChatWidget.h"

AChatPlayerController::AChatPlayerController()
{
	ChatConnection = MakeUnique<FChatConnection>();
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
	ChatWidget = gameInstance->GetChatWidget();
	if (ChatWidget.IsValid())
	{
		ChatWidget->AddToViewport();
		SetShowMouseCursor(true);
		SetInputMode(FInputModeUIOnly());
		AddDelegates();
	}
}

void AChatPlayerController::PlayerTick(float deltaTime)
{
	ChatConnection->Process();
}

void AChatPlayerController::AddDelegates()
{
	if (!ChatWidget.IsValid()) return;
	//�ӽÿ�

	TWeakObjectPtr< AChatPlayerController > thisObjPtr(this);
	ChatWidget->GetConnectBtnPressed().BindLambda(
		[thisObjPtr] (uint32 address, uint32 port)
		{
			if (!thisObjPtr.IsValid()) return;
			AChatPlayerController* thisPtr = thisObjPtr.Get();
			bool connectionResult = thisPtr->ChatConnection->Connect(address, port);
			UE_LOG(LogTemp, Log, TEXT("CALL AChatPlayerController::Connect"));
			if (!thisPtr->ChatWidget.IsValid())
			{
				UE_LOG(LogTemp, Log, TEXT("ChatWidget Unvalid"));
				return;
			}
			if (!thisPtr->ChatWidget.IsValid()) return;
			UChatWidget* chatWidget = thisPtr->ChatWidget.Get();
			if (connectionResult)
			{
				chatWidget->AppendLog(TEXT("Connection Successed!\n"));
			}
			else 
			{
				chatWidget->AppendLog(TEXT("Connection Failed!\n"));
			}
		}
	);

	ChatWidget->GetChatSendBtnPressed().BindLambda(
		[thisObjPtr](const FString& str)
		{
			if (!thisObjPtr.IsValid()) return;
			AChatPlayerController* thisPtr = thisObjPtr.Get();
			thisPtr->ChatConnection->SendText(str);
			UE_LOG(LogTemp, Log, TEXT("CALL AChatPlayerController::SendText"));
		}
	);

	ChatConnection->GetReceivedLine().BindLambda(
		[thisObjPtr](const FString& text) {
			if (!thisObjPtr.IsValid()) return;
			AChatPlayerController* thisPtr = thisObjPtr.Get();
			if (!thisPtr->ChatWidget.IsValid()) return;
			UChatWidget* chatWidget = thisPtr->ChatWidget.Get();
			chatWidget->AppendLog(text);
		}
	);


}
