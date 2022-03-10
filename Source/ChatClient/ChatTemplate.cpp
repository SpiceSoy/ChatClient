// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatTemplate.h"
#include "ChatPageWidget.h"
#include "ConnectWidget.h"
#include "UserListWidget.h"
#include "RoomListWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"


void UChatTemplate::NativeOnInitialized()
{
	TextTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_Title")));
	SetTitle(TEXT("서버 연결하기"));

	TextName = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_Name")));

	ButtonTabConnect = Cast<UButton>(GetWidgetFromName(TEXT("B_T_Connect")));
	ButtonTabConnect->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabConnect);

	ButtonTabLobby = Cast<UButton>(GetWidgetFromName(TEXT("B_T_Lobby")));
	ButtonTabLobby->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabLobby);

	ButtonTabUserList = Cast<UButton>(GetWidgetFromName(TEXT("B_T_UserList")));
	ButtonTabUserList->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabUserList);

	ButtonTabRoomList = Cast<UButton>(GetWidgetFromName(TEXT("B_T_RoomList")));
	ButtonTabRoomList->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabRoomList);

	WidgetSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WS_Main")));

	ConnectWidget = Cast<UConnectWidget>(GetWidgetFromName(TEXT("BPConnect")));

	LobbyWidget = Cast<UChatPageWidget>(GetWidgetFromName(TEXT("BPChatPageLobby")));

	UserListWidget = Cast<UUserListWidget>(GetWidgetFromName(TEXT("BPUserList")));

	RoomListWidget = Cast<URoomListWidget>(GetWidgetFromName(TEXT("BPRoomList")));
}

void UChatTemplate::OnClickedTabConnect()
{
	ChagedTabConnect.ExecuteIfBound();
	SetTitle(TEXT("서버 연결하기"));
	SetWidgetIndex(0);
}

void UChatTemplate::OnClickedTabLobby()
{
	ChagedTabLobby.ExecuteIfBound();
	SetTitle(TEXT("채팅 세션"));
	SetWidgetIndex(1);
}

void UChatTemplate::OnClickedTabUserList()
{
	ChagedTabUserList.ExecuteIfBound();
	SetTitle(TEXT("이용자 목록"));
	SetWidgetIndex(2);
}

void UChatTemplate::OnClickedTabRoomList()
{
	ChagedTabRoomList.ExecuteIfBound();
	SetTitle(TEXT("대화방 목록"));
	SetWidgetIndex(3);
}

void UChatTemplate::SetWidgetIndex(int32 index) const
{
	if (WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(index);
}

void UChatTemplate::SetTitle(const FString& title) const
{
	if(TextTitle) TextTitle->SetText(FText::FromString(title));
}

void UChatTemplate::SetUserName(const FString& title) const
{
	if(TextName) TextName->SetText(FText::FromString(title));
}

TWeakObjectPtr<UConnectWidget> UChatTemplate::GetConnectWidget() const
{
	return MakeWeakObjectPtr(ConnectWidget);
}

TWeakObjectPtr<UChatPageWidget> UChatTemplate::GetLobbyWidget() const
{
	return MakeWeakObjectPtr(LobbyWidget);
}

TWeakObjectPtr<UUserListWidget> UChatTemplate::GetUserListWidget() const
{
	return MakeWeakObjectPtr(UserListWidget);
}

TWeakObjectPtr<URoomListWidget> UChatTemplate::GetRoomListWidget() const
{
	return MakeWeakObjectPtr(RoomListWidget);
}

UChatTemplate::FChangedTab& UChatTemplate::GetChagedTabConnect()
{
	return ChagedTabConnect;
}

UChatTemplate::FChangedTab& UChatTemplate::GetChagedTabLobby()
{
	return ChagedTabLobby;
}

UChatTemplate::FChangedTab& UChatTemplate::GetChagedTabUserList()
{
	return ChagedTabUserList;
}

UChatTemplate::FChangedTab& UChatTemplate::GetChagedTabRoomList()
{
	return ChagedTabRoomList;
}
