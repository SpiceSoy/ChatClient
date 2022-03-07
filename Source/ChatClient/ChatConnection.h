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
	DECLARE_DELEGATE_OneParam(FReceivedLine, const FString&);
public:
	FChatConnection();
	~FChatConnection();

	FReceivedLine ReceivedLine;


	FReceivedLine& GetReceivedLine();
	bool Connect(uint32 address, uint32 port);
	void Process();
private:
	TArray<uint8> RecvBuffer;
	int32 RecvBytes = 0;
	TArray<uint8> SendBuffer;
	int32 SendBytes = 0;
	class FSocket* Socket = nullptr;
	class FRunnableThread* RunRead = nullptr;
	bool IsConnected = false;

private:
	void ProcessRecv();
	void ProcessSend();

	void GrowRecvBuffer();
	void GrowSendBuffer();
	int32 GetRecvBufferSize() const;
	int32 GetSendBufferSize() const;
};
