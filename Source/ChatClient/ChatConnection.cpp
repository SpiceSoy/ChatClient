// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatConnection.h"
#include "Containers/StringConv.h"
#include <codecvt>
#include <vector>

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

void FChatConnection::SendText(const FString& str)
{
	if (GetSendBufferSize() < SendBytes + str.Len() * sizeof(WIDECHAR))
	{
		GrowSendBuffer();
	}
	SendBytes += ConvertToMBCS(str, SendBuffer.GetData() + SendBytes, GetSendBufferSize() - SendBytes);
}

void FChatConnection::ProcessRecv()
{
	int32 byteRecved = 0;
	bool result = Socket->Recv(RecvBuffer.GetData(), RecvBuffer.Num() * RecvBuffer.GetTypeSize(), byteRecved);
	if (result == false)
	{
		//俊矾贸府
	}
	else if (byteRecved != 0)
	{
		RecvBytes += byteRecved;
		if (RecvBytes * 1.5 > GetRecvBufferSize()) GrowRecvBuffer();
		if (RecvBuffer[RecvBytes - 1] == '\n')
		{
			RecvBuffer[RecvBytes - 1] = 0;
			ReceivedLine.Execute(ConvertToWBCS(RecvBuffer.GetData(), RecvBytes));
			RecvBytes = 0;
		}
		UE_LOG(LogTemp, Log, TEXT("CALL FChatConnection::ProcessRecv"));
	}
}

void FChatConnection::ProcessSend()
{
	if (SendBytes == 0) return;
	int32 byteSent = 0;
	bool result = Socket->Send(SendBuffer.GetData(), SendBytes, byteSent);
	if (result == false)
	{
		//俊矾贸府
	}
	else if (byteSent != 0)
	{
		FMemory::Memcpy(SendBuffer.GetData(), SendBuffer.GetData() + byteSent, SendBytes - byteSent);
		UE_LOG(LogTemp, Log, TEXT("CALL FChatConnection::ProcessSend %d"), byteSent);
		SendBytes -= byteSent;
	}
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

FString FChatConnection::ConvertToWBCS(uint8* buffer, uint32 size)
{
	//https://midason.tistory.com/401
	using codecvt_t = std::codecvt<wchar_t, char, std::mbstate_t>;
	std::locale loc = std::locale("");
	codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
	const char* newLast;
	std::vector<wchar_t> wcharBuffer;
	wcharBuffer.resize(size);
	wchar_t* newWCharLast;
	auto state = std::mbstate_t();
	auto result = codecvt.in(state, (const char*)buffer, (const char*)(buffer + size), newLast, wcharBuffer.data(), wcharBuffer.data() + size, newWCharLast);
	return FString(wcharBuffer.data());
}

uint32 FChatConnection::ConvertToMBCS(const FString& srcStr, uint8* destBuffer, uint32 size)
{
	//https://midason.tistory.com/401
	using codecvt_t = std::codecvt<wchar_t, char, std::mbstate_t>;
	std::locale loc = std::locale("");
	codecvt_t const& codecvt = std::use_facet<codecvt_t>(loc);
	char* newLast;
	std::vector<wchar_t> wcharBuffer;
	wcharBuffer.resize(size);
	const wchar_t* newWCharLast;
	auto state = std::mbstate_t();
	auto result = codecvt.out(state, *srcStr, *srcStr + size, newWCharLast, (char*)destBuffer, (char*)(destBuffer + size), newLast);
	return newLast - (char*)destBuffer;
}
