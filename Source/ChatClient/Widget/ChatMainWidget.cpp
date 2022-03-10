//=================================================================================================
// @file ChatMainWidget.h
//
// @brief 위젯 메인 페이지 클래스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Widget/ChatMainWidget.h"
#include "Widget/ChatPage.h"
#include "Widget/ConnectPage.h"
#include "Widget/RoomListPage.h"
#include "Widget/UserListPage.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"


void UChatMainWidget::NativeOnInitialized()
{
	TextTitle = Cast<UTextBlock>( GetWidgetFromName( TEXT( "T_Title" ) ) );

	TextName = Cast<UTextBlock>( GetWidgetFromName( TEXT( "T_Name" ) ) );

	ButtonTabConnect = Cast<UButton>( GetWidgetFromName( TEXT( "B_T_Connect" ) ) );
	ButtonTabConnect->OnClicked.AddDynamic( this, &UChatMainWidget::OnClickedTabConnect );

	ButtonTabLobby = Cast<UButton>( GetWidgetFromName( TEXT( "B_T_Lobby" ) ) );
	ButtonTabLobby->OnClicked.AddDynamic( this, &UChatMainWidget::OnClickedTabChat );

	ButtonTabUserList = Cast<UButton>( GetWidgetFromName( TEXT( "B_T_UserList" ) ) );
	ButtonTabUserList->OnClicked.AddDynamic( this, &UChatMainWidget::OnClickedTabUserList );

	ButtonTabRoomList = Cast<UButton>( GetWidgetFromName( TEXT( "B_T_RoomList" ) ) );
	ButtonTabRoomList->OnClicked.AddDynamic( this, &UChatMainWidget::OnClickedTabRoomList );

	WidgetSwitcher = Cast<UWidgetSwitcher>( GetWidgetFromName( TEXT( "WS_Main" ) ) );

	ConnectWidget = Cast<UConnectPage>( GetWidgetFromName( TEXT( "BPConnect" ) ) );

	ChatPage = Cast<UChatPage>( GetWidgetFromName( TEXT( "BPChatPage" ) ) );

	UserListWidget = Cast<UUserListPage>( GetWidgetFromName( TEXT( "BPUserList" ) ) );

	RoomListWidget = Cast<URoomListPage>( GetWidgetFromName( TEXT( "BPRoomList" ) ) );

	SetTitle( TEXT( "서버 연결하기" ) );
}

void UChatMainWidget::OnClickedTabConnect()
{
	ChagedTabConnect.ExecuteIfBound();
	SetTitle( TEXT( "서버 연결하기" ) );
	SetWidgetIndex( 0 );
}

void UChatMainWidget::OnClickedTabChat()
{
	ChagedTabLobby.ExecuteIfBound();
	SetTitle( TEXT( "채팅 세션" ) );
	SetWidgetIndex( 1 );
}

void UChatMainWidget::OnClickedTabUserList()
{
	ChagedTabUserList.ExecuteIfBound();
	SetTitle( TEXT( "이용자 목록" ) );
	SetWidgetIndex( 2 );
}

void UChatMainWidget::OnClickedTabRoomList()
{
	ChagedTabRoomList.ExecuteIfBound();
	SetTitle( TEXT( "대화방 목록" ) );
	SetWidgetIndex( 3 );
}

void UChatMainWidget::SetWidgetIndex( int32 index ) const
{
	if( WidgetSwitcher ) WidgetSwitcher->SetActiveWidgetIndex( index );
}

void UChatMainWidget::SetTitle( const FString& title ) const
{
	if( TextTitle ) TextTitle->SetText( FText::FromString( title ) );
}

void UChatMainWidget::SetUserName( const FString& title ) const
{
	if( TextName ) TextName->SetText( FText::FromString( title ) );
}

TWeakObjectPtr<UConnectPage> UChatMainWidget::GetConnectPage() const
{
	return MakeWeakObjectPtr( ConnectWidget );
}

TWeakObjectPtr<UChatPage> UChatMainWidget::GetChatPage() const
{
	return MakeWeakObjectPtr( ChatPage );
}

TWeakObjectPtr<UUserListPage> UChatMainWidget::GetUserListPage() const
{
	return MakeWeakObjectPtr( UserListWidget );
}

TWeakObjectPtr<URoomListPage> UChatMainWidget::GetRoomListPage() const
{
	return MakeWeakObjectPtr( RoomListWidget );
}

UChatMainWidget::FChangedTab& UChatMainWidget::GetChagedTabConnect()
{
	return ChagedTabConnect;
}

UChatMainWidget::FChangedTab& UChatMainWidget::GetChagedTabChat()
{
	return ChagedTabLobby;
}

UChatMainWidget::FChangedTab& UChatMainWidget::GetChagedTabUserList()
{
	return ChagedTabUserList;
}

UChatMainWidget::FChangedTab& UChatMainWidget::GetChagedTabRoomList()
{
	return ChagedTabRoomList;
}
