// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatConnection.h"
#include "ChatWidget.h"
#include "ChatTemplate.h"
#include "ChatPageWidget.h"
#include "ConnectWidget.h"
#include "UserListWidget.h"
#include "Command/CommandProcessor.h"
#include "Containers/StringConv.h"
#include <codecvt>
#include <vector>

UChatConnection::UChatConnection()
{
	RecvBuffer.Init(0, 1024);
	SendBuffer.Init(0, 1024);
}

UChatConnection::~UChatConnection()
{
	Close();
}

FCommandProcessor& UChatConnection::GetCommandProcessor()
{
	return CommandProcessor;
}

bool UChatConnection::Connect(uint32 address, uint32 port)
{
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(address);
	addr->SetPort(port);

	IsConnected = Socket->Connect(*addr);
	Socket->SetNonBlocking(true);
	return IsConnected;
}

void UChatConnection::Close()
{
	if (IsConnected)
	{
		Socket->Close();
		OnSessionClosed();
		IsConnected = false;
	}
}

void UChatConnection::Process()
{
	if (!IsConnected) return;
	ProcessRecv();
	ProcessSend();
}

void UChatConnection::SendText(const FString& str)
{
	if (!IsConnected) return;
	if (GetSendBufferSize() < SendBytes + str.Len() * sizeof(WIDECHAR))
	{
		GrowSendBuffer();
	}
	SendBytes += ConvertToMBCS(str, SendBuffer.GetData() + SendBytes, GetSendBufferSize() - SendBytes);
}

void UChatConnection::SetChatUi(const TWeakObjectPtr<UChatTemplate>& ptr)
{
	ChatUi = ptr;
	BindDelegate();
}

//void UChatConnection::SetWidget(const TWeakObjectPtr<UChatWidget>& ptr)
//{
//	ChatWidget = ptr;
//	BindDelegate();
//}

void UChatConnection::OnSessionClosed()
{
	//if (ChatWidget.IsValid()) ChatWidget->AppendLog(TEXT("연결이 종료되었습니다.\n"));
}

void UChatConnection::OnLineReceived(const FString& line)
{
	if (!ChatUi.IsValid()) return;
	TWeakObjectPtr<UChatPageWidget> lobby = ChatUi->GetLobbyWidget();
	if (!lobby.IsValid()) return;
	lobby->AppendLog(line);
}

void UChatConnection::BindDelegate()
{
#pragma region WIDGET
	//if (!ChatWidget.IsValid()) return;

	//TWeakObjectPtr<UChatConnection> thisObjPtr = MakeWeakObjectPtr(this);

	//ChatWidget->GetConnectBtnPressed().BindLambda(
	//	[thisObjPtr](uint32 address, uint32 port)
	//	{
	//		if (!thisObjPtr.IsValid()) return;
	//		UChatConnection* thisPtr = thisObjPtr.Get();
	//		if (!thisPtr->ChatWidget.IsValid()) return;
	//		UChatWidget* chatWidget = thisPtr->ChatWidget.Get();

	//		bool connectionResult = thisPtr->Connect(address, port);
	//		if (connectionResult) chatWidget->AppendLog(TEXT("연결이 성공하였습니다.\n"));
	//		else chatWidget->AppendLog(TEXT("연결이 실패하였습니다.\n"));
	//	}
	//);

	//ChatWidget->GetChatSendBtnPressed().BindLambda(
	//	[thisObjPtr](const FString& str)
	//	{
	//		if (!thisObjPtr.IsValid()) return;
	//		UChatConnection* thisPtr = thisObjPtr.Get();
	//		thisPtr->SendText(str);
	//	}
	//);

	//CommandProcessor.GetChangedUserList().BindLambda(
	//	[thisObjPtr](const TArray<UUserData*>& arr)
	//	{
	//		if (!thisObjPtr.IsValid()) return;
	//		UChatConnection* thisPtr = thisObjPtr.Get();
	//		if (!thisPtr->ChatWidget.IsValid()) return;
	//		UChatWidget* chatWidget = thisPtr->ChatWidget.Get();
	//		chatWidget->SetUserList(arr);
	//	}
	//);
#pragma endregion

	if (!ChatUi.IsValid()) return;
	TWeakObjectPtr<UChatConnection> thisObjPtr = MakeWeakObjectPtr(this);
	TWeakObjectPtr<UChatTemplate> chatWidget = ChatUi;
	TWeakObjectPtr<UConnectWidget> connectWidget = ChatUi->GetConnectWidget();
	TWeakObjectPtr<UUserListWidget> userListWidget = ChatUi->GetUserListWidget();
	TWeakObjectPtr<UChatPageWidget> lobbyWidget = ChatUi->GetLobbyWidget();

	if (!chatWidget.IsValid()) return;
	if (!connectWidget.IsValid()) return;
	if (!userListWidget.IsValid()) return;
	if (!lobbyWidget.IsValid()) return;


	chatWidget->GetChagedTabUserList().BindLambda(
		[thisObjPtr]()
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->SendText("US");
		}
	);

	lobbyWidget->GetClickedSend().BindLambda(
		[thisObjPtr](const FString& str)
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->SendText(str);
		}
	);

	connectWidget->GetClickedConnectBtn().BindLambda(
		[thisObjPtr, connectWidget](uint32 address, uint32 port)
		{
			UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::BINDLAMBDA_CLICKED_START"));
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if (!connectWidget.IsValid()) return;
			UConnectWidget* chatWidget = connectWidget.Get();


			bool connectionResult = thisPtr->Connect(address, port);
			if (connectionResult) chatWidget->SetConnectionInfoText(TEXT("연결이 성공하였습니다.\n"));
			else chatWidget->SetConnectionInfoText(TEXT("연결이 실패하였습니다.\n"));
			UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::BINDLAMBDA_CLICKED_END"));
		}
	);

	connectWidget->GetClickedLoginBtn().BindLambda(
		[thisObjPtr, connectWidget, chatWidget](const FString& name)
		{
			UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::BINDLAMBDA_CLICKED_START"));
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if (!connectWidget.IsValid()) return;
			UConnectWidget* connectWidgetPtr = connectWidget.Get();
			if (!chatWidget.IsValid()) return;
			UChatTemplate* chatWidgetPtr = chatWidget.Get();

			FString idCommand = FString::Printf(TEXT("LOGIN %s"), *name);
			thisPtr->SendText(idCommand);
			chatWidgetPtr->SetWidgetIndex(1);
			UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::BINDLAMBDA_CLICKED_END"));
		}
	);

	CommandProcessor.GetChangedUserList().BindLambda(
		[thisObjPtr, userListWidget](const TArray<UUserData*>& arr)
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if (!userListWidget.IsValid()) return;
			UUserListWidget* userListWidgetPtr = userListWidget.Get();
			userListWidgetPtr->SetUserList(arr);
		}
	);


}

void UChatConnection::ProcessRecv()
{
	int32 byteRecved = 0;
	bool result = Socket->Recv(RecvBuffer.GetData(), RecvBuffer.Num() * RecvBuffer.GetTypeSize(), byteRecved);
	if (result == false)
	{
		Close();
	}
	else if (byteRecved != 0)
	{
		RecvBytes += byteRecved;
		uint8* csrLast = RecvBuffer.GetData();
		uint8* csrBegin = RecvBuffer.GetData();
		while (csrLast != (RecvBuffer.GetData() + RecvBytes))
		{
			if (*csrLast == '\n')
			{
				*csrLast = 0;
				FString line = ConvertToWBCS(csrBegin, csrLast - csrBegin + 1);
				if (CommandProcessor.ProcessLine(line)) OnLineReceived(line);
				csrLast++;
				csrBegin = csrLast;
			}
			else
			{
				csrLast++;
			}
		}
		if (csrBegin != csrLast)
		{
			FMemory::Memcpy(RecvBuffer.GetData(), csrBegin, csrLast - csrBegin + 1);
		}
		RecvBytes = 0;
		UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::ProcessRecv"));
	}
}

void UChatConnection::ProcessSend()
{
	if (SendBytes == 0) return;
	int32 byteSent = 0;
	bool result = Socket->Send(SendBuffer.GetData(), SendBytes, byteSent);
	if (result == false)
	{
		Close();
	}
	else if (byteSent != 0)
	{
		FMemory::Memcpy(SendBuffer.GetData(), SendBuffer.GetData() + byteSent, SendBytes - byteSent);
		UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::ProcessSend %d"), byteSent);
		SendBytes -= byteSent;
	}
}

void UChatConnection::GrowRecvBuffer()
{
	RecvBuffer.SetNum(RecvBuffer.Num() * 2);
}

void UChatConnection::GrowSendBuffer()
{
	SendBuffer.SetNum(SendBuffer.Num() * 2);
}

int32 UChatConnection::GetRecvBufferSize() const
{
	return RecvBuffer.Num() * RecvBuffer.GetTypeSize();
}

int32 UChatConnection::GetSendBufferSize() const
{
	return SendBuffer.Num() * SendBuffer.GetTypeSize();
}

FString UChatConnection::ConvertToWBCS(uint8* buffer, uint32 size)
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

uint32 UChatConnection::ConvertToMBCS(const FString& srcStr, uint8* destBuffer, uint32 size)
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
