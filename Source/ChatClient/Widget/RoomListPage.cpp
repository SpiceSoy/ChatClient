// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/RoomListPage.h"
#include "RoomData.h"
#include "Components/ListView.h"

void URoomListPage::NativeOnInitialized()
{
	ListViewRoom = Cast<UListView>(GetWidgetFromName(TEXT("LV_Room")));
}

void URoomListPage::SetRoomList(const TArray<URoomData*>& arr)
{
	if(ListViewRoom)
	{
		ListViewRoom->ClearListItems();
		ListViewRoom->SetListItems(arr);
	}
}
