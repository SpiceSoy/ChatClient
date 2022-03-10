//=================================================================================================
// @file RoomListPage.h
//
// @brief 이용자 목록 UI 페이지를 위한 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Widget/UserListPage.h"
#include "UserData.h"
#include "Components/ListView.h"


void UUserListPage::NativeOnInitialized()
{
	ListViewUser = Cast<UListView>(GetWidgetFromName(TEXT("LV_User")));
}

void UUserListPage::SetUserList(const TArray<UUserData*>& arr) const
{
	if(ListViewUser) ListViewUser->SetListItems(arr);
}
