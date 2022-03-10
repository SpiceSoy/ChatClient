//=================================================================================================
// @file ChatConnection.h
//
// @brief 채팅 서버와 소켓 통신을 하기 위한 클래스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Command/CommandProcessor.h"
#include "CoreMinimal.h"
#include "Containers/Queue.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "ChatConnection.generated.h"


/**
 * 
 */
 UCLASS()
class CHATCLIENT_API UChatConnection : public UObject
{

	 GENERATED_BODY()
private:
	TArray<uint8> RecvBuffer;
	int32 RecvBytes = 0;
	TArray<uint8> SendBuffer;
	int32 SendBytes = 0;

	class FSocket* Socket = nullptr;

	bool IsConnected = false;
	bool IsLogin = false;
	bool IsInRoom = false;

	TWeakObjectPtr<UChatTemplate> ChatUi;
	FCommandProcessor CommandProcessor;
	FString Name;
public:
	UChatConnection();
	~UChatConnection();
	FCommandProcessor& GetCommandProcessor();

	bool Connect(uint32 address, uint32 port);
	void Close();
	void Process();
	void SendText(const FString& str);
	void SendCommand(const FString& str);
	void SetChatUi(const TWeakObjectPtr<class UChatTemplate>& ptr);

	void OnSessionClosed();
	void OnLineReceived(const FString& line);
	void BindDelegate();

	bool GetLogin() const;
	void SetLogin(bool isLogin);

private:
	void ProcessRecv();
	void ProcessSend();

	void GrowRecvBuffer();
	void GrowSendBuffer();
	int32 GetRecvBufferSize() const;
	int32 GetSendBufferSize() const;

	static FString ConvertToWBCS(uint8* srcBuffer, uint32 size);
	static uint32 ConvertToMBCS(const FString& srcStr, uint8* destBuffer, uint32 size);
};
