//=================================================================================================
// @file ChatConnection.h
//
// @brief utill class to connect chat server and recv, send packets 
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Containers/Queue.h"

/**
 * 
 */
class CHATCLIENT_API FChatConnection
{
	DECLARE_DELEGATE_OneParam(FLineReceived, const FString&);
	DECLARE_DELEGATE(FClosedSession);
public:
	FChatConnection();
	~FChatConnection();

	FLineReceived& GetLineReceived();
	FClosedSession& GetClosedSession();

	bool Connect(uint32 address, uint32 port);
	void Close();
	void Process();
	void SendText(const FString& str);
private:
	TArray<uint8> RecvBuffer;
	int32 RecvBytes = 0;
	TArray<uint8> SendBuffer;
	int32 SendBytes = 0;
	class FSocket* Socket = nullptr;
	class FRunnableThread* RunRead = nullptr;
	bool IsConnected = false;

	FLineReceived LineReceived;
	FClosedSession ClosedSession;
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
