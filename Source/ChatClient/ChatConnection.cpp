// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatConnection.h"
#include "ChatWidget.h"
#include "ChatTemplate.h"
#include "ChatPageWidget.h"
#include "ConnectWidget.h"
#include "UserListWidget.h"
#include "RoomListWidget.h"
#include "Command/CommandProcessor.h"
#include "Containers/StringConv.h"
#include <codecvt>
#include <vector>
#include <stdlib.h>

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
	if(IsConnected) return true;
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(address);
	addr->SetPort(port);

	IsConnected = Socket->Connect(*addr);
	Socket->SetNonBlocking(true);
	Socket->SetNoDelay(true);
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
	bool bufferSizeWillOver = GetSendBufferSize() < SendBytes + str.Len() * sizeof(WIDECHAR);
	if (bufferSizeWillOver) GrowSendBuffer();
	SendBytes += ConvertToMBCS(str, SendBuffer.GetData() + SendBytes, GetSendBufferSize() - SendBytes);
}

void UChatConnection::SendCommand(const FString& str)
{
	static const FString prefix = TEXT("/");
	if(IsInRoom) SendText(prefix + str);
	else SendText(str);
}

void UChatConnection::SetChatUi(const TWeakObjectPtr<UChatTemplate>& ptr)
{
	ChatUi = ptr;
	BindDelegate();
}

void UChatConnection::OnSessionClosed()
{
	if (!ChatUi.IsValid()) return;
	ChatUi->SetUserName(TEXT("연결 종료됨"));
	ChatUi->OnClickedTabConnect();
	TWeakObjectPtr<UConnectWidget> connectWidget = ChatUi->GetConnectWidget();
	if(!connectWidget.IsValid()) return;
	connectWidget->SetConnectionInfoText(TEXT("연결이 종료되었습니다."));
	IsConnected = false;
	IsLogin = false;
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
	if (!ChatUi.IsValid()) return;
	TWeakObjectPtr<UChatConnection> thisObjPtr = MakeWeakObjectPtr(this);
	TWeakObjectPtr<UChatTemplate> chatWidget = ChatUi;
	TWeakObjectPtr<UConnectWidget> connectWidget = ChatUi->GetConnectWidget();
	TWeakObjectPtr<UUserListWidget> userListWidget = ChatUi->GetUserListWidget();
	TWeakObjectPtr<URoomListWidget> roomListWidget = ChatUi->GetRoomListWidget();
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
			thisPtr->SendCommand(TEXT("US"));
		}
	);
	chatWidget->GetChagedTabRoomList().BindLambda(
		[thisObjPtr]()
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->SendCommand(TEXT("LT"));
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
		[thisObjPtr, connectWidget, chatWidget](uint32 address, uint32 port)
		{
			UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::BINDLAMBDA_CLICKED_START"));
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if (!connectWidget.IsValid()) return;
			UConnectWidget* connectWidgetPtr = connectWidget.Get();
			if (!chatWidget.IsValid()) return;
			UChatTemplate* chatWidgetPtr = chatWidget.Get();

			if(thisPtr->IsConnected)
			{
				connectWidgetPtr->SetConnectionInfoText(TEXT("이미 연결 중입니다."));
				return;
			}

			bool connectionResult = thisPtr->Connect(address, port);
			if (connectionResult)
			{
				connectWidgetPtr->SetConnectionInfoText(TEXT("연결이 성공하였습니다."));
				chatWidgetPtr->SetUserName(TEXT("로그인 대기 중"));
			}
			else 
			{
				connectWidgetPtr->SetConnectionInfoText(TEXT("연결이 실패하였습니다."));
			}
			UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::BINDLAMBDA_CLICKED_END"));
		}
	);

	connectWidget->GetClickedLoginBtn().BindLambda(
		[thisObjPtr, connectWidget](const FString& name)
		{
			UE_LOG(LogTemp, Log, TEXT("CALL UChatConnection::BINDLAMBDA_CLICKED_START"));
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if (!connectWidget.IsValid()) return;
			UConnectWidget* connectWidgetPtr = connectWidget.Get();

			if(thisPtr->IsLogin)
			{
				connectWidgetPtr->SetConnectionInfoText(TEXT("이미 로그인 중입니다."));
				return;
			}

			FString idCommand = FString::Printf(TEXT("LOGIN %s"), *name);
			thisPtr->SendText(idCommand);
			thisPtr->Name = name;
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

	CommandProcessor.GetChangedRoomList().BindLambda(
		[thisObjPtr, roomListWidget](const TArray<URoomData*>& arr)
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if (!roomListWidget.IsValid()) return;
			URoomListWidget* roomListWidgetPtr = roomListWidget.Get();

			for (URoomData* data : arr) data->SetConnection(thisObjPtr);

			roomListWidgetPtr->SetRoomList(arr);
		}
	);

	CommandProcessor.GetSucceededLogin().BindLambda(
		[thisObjPtr]()
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->SetLogin(true);
		}
	);

	CommandProcessor.GetFailedLogin().BindLambda(
		[thisObjPtr, connectWidget](const FString& info)
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if (!connectWidget.IsValid()) return;
			UConnectWidget* connectWidgetPtr = connectWidget.Get();
			connectWidgetPtr->SetConnectionInfoText(info);
		}
	);

	CommandProcessor.GetEnteredRoom().BindLambda(
		[thisObjPtr, chatWidget]()
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->IsInRoom = true;

			if (!chatWidget.IsValid()) return;
			UChatTemplate* chatWidgetPtr = chatWidget.Get();
			chatWidgetPtr->OnClickedTabLobby();
		}
	);

	CommandProcessor.GetExitedRoom().BindLambda(
		[thisObjPtr]()
		{
			if (!thisObjPtr.IsValid()) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->IsInRoom = false;
		}
	);

}

void UChatConnection::SetLogin(bool isLogin)
{
	IsLogin = isLogin;
	if(isLogin)
	{
		ChatUi->SetUserName(Name);
		ChatUi->OnClickedTabLobby();
	}
}

bool UChatConnection::GetLogin() const
{
	return IsLogin;
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
		//RecvBytes += byteRecved;
		uint8* csrBegin = RecvBuffer.GetData();
		uint8* csrLast = RecvBuffer.GetData() + RecvBytes;
		uint8* csrEnd= RecvBuffer.GetData() + RecvBytes + byteRecved;
		while (csrLast != csrEnd)
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
			FMemory::Memcpy(RecvBuffer.GetData(), csrBegin, csrEnd - csrBegin);
			RecvBytes = csrEnd - csrBegin;
		}
		else
		{
			RecvBytes = 0;
		}
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
	return strlen((const char*)destBuffer) + 1;
}

