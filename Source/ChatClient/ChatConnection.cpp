//=================================================================================================
// @file ChatConnection.h
//
// @brief 채팅 서버와 소켓 통신을 하기 위한 클래스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "ChatConnection.h"
#include "Command/CommandProcessor.h"
#include "Widget/ChatPage.h"
#include "Widget/ChatMainWidget.h"
#include "Widget/ConnectPage.h"
#include "Widget/RoomListPage.h"
#include "Widget/UserListPage.h"
#include "Containers/StringConv.h"
#include <codecvt>
#include <vector>
#include <stdlib.h>


UChatConnection::UChatConnection()
{
	RecvBuffer.Init( 0, 1024 );
	SendBuffer.Init( 0, 1024 );
}

UChatConnection::~UChatConnection()
{
	Close();
}

FCommandProcessor& UChatConnection::GetCommandProcessor()
{
	return CommandProcessor;
}

bool UChatConnection::Connect( uint32 address, uint32 port )
{
	if( IsConnected ) return true;
	Socket = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateSocket( NAME_Stream, TEXT( "default" ), false );

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get( PLATFORM_SOCKETSUBSYSTEM )->CreateInternetAddr();
	addr->SetIp( address );
	addr->SetPort( port );

	IsConnected = Socket->Connect( *addr );
	Socket->SetNonBlocking( true );
	Socket->SetNoDelay( true );
	return IsConnected;
}

void UChatConnection::Close()
{
	if( IsConnected )
	{
		Socket->Close();
		OnSessionClosed();
		IsConnected = false;
	}
}

void UChatConnection::Process()
{
	if( !IsConnected ) return;
	ProcessRecv();
	ProcessSend();
}

void UChatConnection::SendText( const FString& str )
{
	if( !IsConnected ) return;
	bool bufferSizeWillOver = GetSendBufferSize() < SendBytes + str.Len() * sizeof( WIDECHAR );
	if( bufferSizeWillOver ) GrowSendBuffer();
	SendBytes += ConvertToMBCS( str, SendBuffer.GetData() + SendBytes, GetSendBufferSize() - SendBytes );
}

void UChatConnection::SendCommand( const FString& str )
{
	static const FString prefix = TEXT( "/" );
	if( IsInRoom ) SendText( prefix + str );
	else SendText( str );
}

void UChatConnection::SetChatUi( const TWeakObjectPtr<UChatMainWidget>& ptr )
{
	ChatUi = ptr;
	BindDelegate();
}

void UChatConnection::OnSessionClosed()
{
	if( !ChatUi.IsValid() ) return;
	ChatUi->SetUserName( TEXT( "연결 종료됨" ) );
	ChatUi->OnClickedTabConnect();
	TWeakObjectPtr<UConnectPage> connectWidget = ChatUi->GetConnectPage();
	if( !connectWidget.IsValid() ) return;
	connectWidget->SetConnectionInfoText( TEXT( "연결이 종료되었습니다." ) );
	CommandProcessor.TurnOnLoginState();
	IsConnected = false;
	IsLogin = false;
}

void UChatConnection::OnLineReceived( const FString& line )
{
	if( !ChatUi.IsValid() ) return;
	TWeakObjectPtr<UChatPage> lobby = ChatUi->GetChatPage();
	if( !lobby.IsValid() ) return;
	lobby->AppendLog( line );
}

void UChatConnection::BindDelegate()
{
	if( !ChatUi.IsValid() ) return;
	TWeakObjectPtr<UChatConnection> thisObjPtr = MakeWeakObjectPtr( this );
	TWeakObjectPtr<UChatMainWidget> chatWidget = ChatUi;
	TWeakObjectPtr<UConnectPage> connectPage = ChatUi->GetConnectPage();
	TWeakObjectPtr<UUserListPage> userListPage = ChatUi->GetUserListPage();
	TWeakObjectPtr<URoomListPage> roomListPage = ChatUi->GetRoomListPage();
	TWeakObjectPtr<UChatPage> chatPage = ChatUi->GetChatPage();

	if( !chatWidget.IsValid() ) return;
	if( !connectPage.IsValid() ) return;
	if( !userListPage.IsValid() ) return;
	if( !chatPage.IsValid() ) return;


	chatWidget->GetChagedTabUserList().BindLambda(
		[thisObjPtr] ()
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->SendCommand( TEXT( "US" ) );
		}
	);
	chatWidget->GetChagedTabRoomList().BindLambda(
		[thisObjPtr] ()
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->SendCommand( TEXT( "LT" ) );
		}
	);

	chatPage->GetClickedSend().BindLambda(
		[thisObjPtr] ( const FString& str )
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->SendText( str );
		}
	);

	connectPage->GetClickedConnectBtn().BindLambda(
		[thisObjPtr, connectPage, chatWidget] ( uint32 address, uint32 port )
		{
			UE_LOG( LogTemp, Log, TEXT( "CALL UChatConnection::BINDLAMBDA_CLICKED_START" ) );
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if( !connectPage.IsValid() ) return;
			UConnectPage* connectPagePtr = connectPage.Get();
			if( !chatWidget.IsValid() ) return;
			UChatMainWidget* chatWidgetPtr = chatWidget.Get();

			if( thisPtr->IsConnected )
			{
				connectPagePtr->SetConnectionInfoText( TEXT( "이미 연결 중입니다." ) );
				return;
			}

			bool connectionResult = thisPtr->Connect( address, port );
			if( connectionResult )
			{
				connectPagePtr->SetConnectionInfoText( TEXT( "연결이 성공하였습니다." ) );
				chatWidgetPtr->SetUserName( TEXT( "로그인 대기 중" ) );
			}
			else
			{
				connectPagePtr->SetConnectionInfoText( TEXT( "연결이 실패하였습니다." ) );
			}
			UE_LOG( LogTemp, Log, TEXT( "CALL UChatConnection::BINDLAMBDA_CLICKED_END" ) );
		}
	);

	connectPage->GetClickedLoginBtn().BindLambda(
		[thisObjPtr, connectPage] ( const FString& name )
		{
			UE_LOG( LogTemp, Log, TEXT( "CALL UChatConnection::BINDLAMBDA_CLICKED_START" ) );
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if( !connectPage.IsValid() ) return;
			UConnectPage* connectPagePtr = connectPage.Get();

			if( thisPtr->IsLogin )
			{
				connectPagePtr->SetConnectionInfoText( TEXT( "이미 로그인 중입니다." ) );
				return;
			}

			FString idCommand = FString::Printf( TEXT( "LOGIN %s" ), *name );
			thisPtr->SendText( idCommand );
			thisPtr->Name = name;
			UE_LOG( LogTemp, Log, TEXT( "CALL UChatConnection::BINDLAMBDA_CLICKED_END" ) );
		}
	);

	CommandProcessor.GetChangedUserList().BindLambda(
		[thisObjPtr, userListPage, chatWidget] ( const TArray<UUserData*>& arr )
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if( !userListPage.IsValid() ) return;
			UUserListPage* userListPagePtr = userListPage.Get();

			for( UUserData* data : arr ) data->SetPtr( thisObjPtr, chatWidget );

			userListPagePtr->SetUserList( arr );
		}
	);

	CommandProcessor.GetChangedRoomList().BindLambda(
		[thisObjPtr, roomListPage, chatWidget] ( const TArray<URoomData*>& arr )
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if( !roomListPage.IsValid() ) return;
			URoomListPage* roomListPagePtr = roomListPage.Get();

			for( URoomData* data : arr ) data->SetPtr( thisObjPtr, chatWidget );

			roomListPagePtr->SetRoomList( arr );
		}
	);

	CommandProcessor.GetSucceededLogin().BindLambda(
		[thisObjPtr] ()
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->SetLogin( true );
		}
	);

	CommandProcessor.GetFailedLogin().BindLambda(
		[thisObjPtr, connectPage] ( const FString& info )
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			if( !connectPage.IsValid() ) return;
			UConnectPage* connectPagePtr = connectPage.Get();
			connectPagePtr->SetConnectionInfoText( info );
		}
	);

	CommandProcessor.GetEnteredRoom().BindLambda(
		[thisObjPtr, chatWidget, chatPage] ()
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->IsInRoom = true;

			if( !chatWidget.IsValid() ) return;
			UChatMainWidget* chatPagePtr = chatWidget.Get();
			chatPagePtr->OnClickedTabChat();

			if( !chatPage.IsValid() ) return;
			UChatPage* lobbyPagePtr = chatPage.Get();
			lobbyPagePtr->SetChatRoom( true );
		}
	);

	CommandProcessor.GetExitedRoom().BindLambda(
		[thisObjPtr, chatPage] ()
		{
			if( !thisObjPtr.IsValid() ) return;
			UChatConnection* thisPtr = thisObjPtr.Get();
			thisPtr->IsInRoom = false;

			if( !chatPage.IsValid() ) return;
			UChatPage* lobbyPagePtr = chatPage.Get();
			lobbyPagePtr->SetChatRoom( false );

		}
	);

}

void UChatConnection::SetLogin( bool isLogin )
{
	IsLogin = isLogin;
	if( isLogin )
	{
		ChatUi->SetUserName( Name );
		ChatUi->OnClickedTabChat();
	}
}

bool UChatConnection::GetLogin() const
{
	return IsLogin;
}

void UChatConnection::ProcessRecv()
{
	int32 byteRecved = 0;
	bool result = Socket->Recv( RecvBuffer.GetData(), RecvBuffer.Num() * RecvBuffer.GetTypeSize(), byteRecved );
	if( result == false )
	{
		Close();
	}
	else if( byteRecved != 0 )
	{
		//RecvBytes += byteRecved;
		uint8* csrBegin = RecvBuffer.GetData();
		uint8* csrLast = RecvBuffer.GetData() + RecvBytes;
		uint8* csrEnd = RecvBuffer.GetData() + RecvBytes + byteRecved;
		while( csrLast != csrEnd )
		{
			if( *csrLast == '\n' )
			{
				*csrLast = 0;
				FString line = ConvertToWBCS( csrBegin, csrLast - csrBegin + 1 );
				if( CommandProcessor.ProcessLine( line ) ) OnLineReceived( line );
				csrLast++;
				csrBegin = csrLast;
			}
			else
			{
				csrLast++;
			}
		}
		if( csrBegin != csrLast )
		{
			FMemory::Memcpy( RecvBuffer.GetData(), csrBegin, csrEnd - csrBegin );
			RecvBytes = csrEnd - csrBegin;
		}
		else
		{
			RecvBytes = 0;
		}
		UE_LOG( LogTemp, Log, TEXT( "CALL UChatConnection::ProcessRecv" ) );
	}
}

void UChatConnection::ProcessSend()
{
	if( SendBytes == 0 ) return;
	int32 byteSent = 0;
	bool result = Socket->Send( SendBuffer.GetData(), SendBytes, byteSent );
	if( result == false )
	{
		Close();
	}
	else if( byteSent != 0 )
	{
		FMemory::Memcpy( SendBuffer.GetData(), SendBuffer.GetData() + byteSent, SendBytes - byteSent );
		UE_LOG( LogTemp, Log, TEXT( "CALL UChatConnection::ProcessSend %d" ), byteSent );
		SendBytes -= byteSent;
	}
}

void UChatConnection::GrowRecvBuffer()
{
	RecvBuffer.SetNum( RecvBuffer.Num() * 2 );
}

void UChatConnection::GrowSendBuffer()
{
	SendBuffer.SetNum( SendBuffer.Num() * 2 );
}

int32 UChatConnection::GetRecvBufferSize() const
{
	return RecvBuffer.Num() * RecvBuffer.GetTypeSize();
}

int32 UChatConnection::GetSendBufferSize() const
{
	return SendBuffer.Num() * SendBuffer.GetTypeSize();
}

FString UChatConnection::ConvertToWBCS( uint8* buffer, uint32 size )
{
	//https://midason.tistory.com/401
	using codecvt_t = std::codecvt<wchar_t, char, std::mbstate_t>;
	std::locale loc = std::locale( "" );
	codecvt_t const& codecvt = std::use_facet<codecvt_t>( loc );
	const char* newLast;
	std::vector<wchar_t> wcharBuffer;
	wcharBuffer.resize( size );
	wchar_t* newWCharLast;
	auto state = std::mbstate_t();
	auto result = codecvt.in( state, (const char*)buffer, (const char*)( buffer + size ), newLast, wcharBuffer.data(), wcharBuffer.data() + size, newWCharLast );
	return FString( wcharBuffer.data() );
}

uint32 UChatConnection::ConvertToMBCS( const FString& srcStr, uint8* destBuffer, uint32 size )
{
	//https://midason.tistory.com/401
	using codecvt_t = std::codecvt<wchar_t, char, std::mbstate_t>;
	std::locale loc = std::locale( "" );
	codecvt_t const& codecvt = std::use_facet<codecvt_t>( loc );
	char* newLast;
	std::vector<wchar_t> wcharBuffer;
	wcharBuffer.resize( size );
	const wchar_t* newWCharLast;
	auto state = std::mbstate_t();
	auto result = codecvt.out( state, *srcStr, *srcStr + size, newWCharLast, (char*)destBuffer, (char*)( destBuffer + size ), newLast );
	return strlen( (const char*)destBuffer ) + 1;
}

