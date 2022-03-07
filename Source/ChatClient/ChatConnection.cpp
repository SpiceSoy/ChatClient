// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatConnection.h"
#include "Containers/StringConv.h"

FChatConnection::FChatConnection()
{
	RecvBuffer.Init(0, 1024);
	SendBuffer.Init(0, 1024);
}

FChatConnection::~FChatConnection()
{
}

FChatConnection::FReceivedLine& FChatConnection::GetReceivedLine()
{
	return ReceivedLine;
}

bool FChatConnection::Connect(uint32 address, uint32 port)
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(address);
	addr->SetPort(port);

	IsConnected = Socket->Connect(*addr);
	Socket->SetNonBlocking(true);
	return IsConnected;
}

void FChatConnection::Process()
{
	if (!IsConnected) return;
	ProcessRecv();
	ProcessSend();
}

void FChatConnection::ProcessRecv()
{
	int32 byteRecved = 0;
	bool result = Socket->Recv(RecvBuffer.GetData(), RecvBuffer.Num() * RecvBuffer.GetTypeSize(), byteRecved);
	if (result == false)
	{
		//에러처리
	}
	else if (byteRecved != 0)
	{
		RecvBytes += byteRecved;
		if (RecvBytes * 1.5 > GetRecvBufferSize()) GrowRecvBuffer();
		if (RecvBuffer[RecvBytes - 1] == '\n')
		{
			ReceivedLine.Execute(UTF8_TO_TCHAR((ANSICHAR*)RecvBuffer.GetData()));
			RecvBytes = 0;
		}
	}
}

void FChatConnection::ProcessSend()
{
}

void FChatConnection::GrowRecvBuffer()
{
	RecvBuffer.SetNum(RecvBuffer.Num() * 2);
}

void FChatConnection::GrowSendBuffer()
{
	SendBuffer.SetNum(SendBuffer.Num() * 2);
}

int32 FChatConnection::GetRecvBufferSize() const
{
	return RecvBuffer.Num() * RecvBuffer.GetTypeSize();
}

int32 FChatConnection::GetSendBufferSize() const
{
	return SendBuffer.Num() * SendBuffer.GetTypeSize();
}
