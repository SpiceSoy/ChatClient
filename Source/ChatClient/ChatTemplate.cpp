// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatTemplate.h"
#include "ChatPageWidget.h"
#include "ConnectWidget.h"
#include "UserListWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"


void UChatTemplate::NativeOnInitialized()
{
	ButtonTabConnect = Cast<UButton>(GetWidgetFromName(TEXT("B_T_Connect")));
	ButtonTabConnect->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabConnect);

	ButtonTabLobby = Cast<UButton>(GetWidgetFromName(TEXT("B_T_Lobby")));
	ButtonTabLobby->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabLobby);

	ButtonTabUserList = Cast<UButton>(GetWidgetFromName(TEXT("B_T_UserList")));
	ButtonTabUserList->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabUserList);

	WidgetSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WS_Main")));

	ConnectWidget = Cast<UConnectWidget>(GetWidgetFromName(TEXT("BPConnect")));

	LobbyWidget = Cast<UChatPageWidget>(GetWidgetFromName(TEXT("BPChatPageLobby")));
	LobbyWidget->SetTitle(TEXT("로비"));

	UserListWidget = Cast<UUserListWidget>(GetWidgetFromName(TEXT("BPUserList")));
}

void UChatTemplate::OnClickedTabConnect()
{
	ChagedTabConnect.ExecuteIfBound();
	SetWidgetIndex(0);
}

void UChatTemplate::OnClickedTabLobby()
{
	ChagedTabLobby.ExecuteIfBound();
	SetWidgetIndex(1);
}

void UChatTemplate::OnClickedTabUserList()
{
	ChagedTabUserList.ExecuteIfBound();
	SetWidgetIndex(2);
}

void UChatTemplate::SetWidgetIndex(int32 index) const
{
	if (WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(index);
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
