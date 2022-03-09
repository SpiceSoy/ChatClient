// Fill out your copyright notice in the Description page of Project Settings.


#include "UserListWidget.h"
#include "UserData.h"
#include "Components/ListView.h"

void UUserListWidget::NativeOnInitialized()
{
	ListViewUser = Cast<UListView>(GetWidgetFromName(TEXT("LV_User")));
}

void UUserListWidget::SetUserList(const TArray<UUserData*>& arr) const
{
	if(ListViewUser) ListViewUser->SetListItems(arr);
}
