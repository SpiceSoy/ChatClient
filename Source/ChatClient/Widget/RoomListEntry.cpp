//=================================================================================================
// @file RoomListEntry.cpp
//
// @brief 대화방 목록의 리스트뷰 내부 엔트리를 위한 클래스입니다.
//
// @date 2022/03/10
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Widget/RoomListEntry.h"
#include "ChatConnection.h"
#include "RoomData.h"
#include "Widget/RoomListEntryInternal.h"


constexpr const TCHAR* ID_TB_TITLE = TEXT( "TB_Title" );

void URoomListEntry::NativeOnInitialized()
{
	roomListInternalWidget = Cast<URoomListEntryInternal>( GetWidgetFromName( TEXT( "BPRoomEntryInternal" ) ) );
}

void URoomListEntry::NativeOnListItemObjectSet( UObject* listItemObject )
{
	URoomData* roomData = Cast<URoomData>( listItemObject );
	if( roomListInternalWidget ) roomListInternalWidget->Set( roomData );
}

void URoomListEntry::NativeOnItemSelectionChanged( bool isSelected )
{
}
