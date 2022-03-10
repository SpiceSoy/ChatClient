// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomListItem.h"
#include "RoomData.h"
#include "ChatConnection.h"
#include "RoomListItemInternal.h"


constexpr const TCHAR* ID_TB_TITLE = TEXT("TB_Title");

void URoomListItem::NativeOnInitialized()
{
	roomListInternalWidget = Cast<URoomListItemInternal>(GetWidgetFromName(TEXT("BPRoomEntryInternal")));
}

void URoomListItem::NativeOnListItemObjectSet(UObject* listItemObject)
{
	URoomData* roomData = Cast<URoomData>(listItemObject);
	if(roomListInternalWidget) roomListInternalWidget->Set(roomData);
}

void URoomListItem::NativeOnItemSelectionChanged(bool isSelected)
{
}
