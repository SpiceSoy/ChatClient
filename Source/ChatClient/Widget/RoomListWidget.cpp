// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomListWidget.h"
#include "RoomData.h"
#include "Components/ListView.h"

void URoomListWidget::NativeOnInitialized()
{
	ListViewRoom = Cast<UListView>(GetWidgetFromName(TEXT("LV_Room")));
}

void URoomListWidget::SetRoomList(const TArray<URoomData*>& arr)
{
	if(ListViewRoom)
	{
		ListViewRoom->ClearListItems();
		ListViewRoom->SetListItems(arr);
	}
}
