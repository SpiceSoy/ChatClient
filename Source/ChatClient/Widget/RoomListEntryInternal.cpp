//=================================================================================================
// @file RoomListEntryInternal.cpp
//
// @brief RoomListEntry가 실시간 반영이 불가능해서 실시간 갱신을 위해 만든 내부 위젯입니다.
//
// @date 2022/03/10
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "RoomListEntryInternal.h"
#include "ChatConnection.h"
#include "RoomData.h"
#include "Widget/ChatMainWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void URoomListEntryInternal::Set( URoomData* roomData )
{
	RoomData = roomData;
	TWeakObjectPtr<URoomListEntryInternal> thisObjPtr = MakeWeakObjectPtr( this );
	if( RoomData ) RoomData->GetChangedData().BindLambda(
		[thisObjPtr] ()
		{
			if( !thisObjPtr.IsValid() ) return;
			URoomListEntryInternal* thisPtr = thisObjPtr.Get();
			thisPtr->OnDataChanged();
		}
	);
	OnDataChanged();
}

void URoomListEntryInternal::NativeOnInitialized()
{
	TextName = Cast<UTextBlock>( GetWidgetFromName( TEXT( "TB_RoomName" ) ) );
	TextIndex = Cast<UTextBlock>( GetWidgetFromName( TEXT( "TB_Index" ) ) );
	TextUser = Cast<UTextBlock>( GetWidgetFromName( TEXT( "TB_User" ) ) );

	ButtonView = Cast<UButton>( GetWidgetFromName( TEXT( "BTN_View" ) ) );
	ButtonView->OnClicked.AddDynamic( this, &URoomListEntryInternal::OnClickedViewButton );
	ButtonEnter = Cast<UButton>( GetWidgetFromName( TEXT( "BTN_Enter" ) ) );
	ButtonEnter->OnClicked.AddDynamic( this, &URoomListEntryInternal::OnClickedEnterButton );
}

void URoomListEntryInternal::NativeTick( const FGeometry& myGeometry, float inDeltaTime )
{

}


void URoomListEntryInternal::OnClickedViewButton()
{
	if( !RoomData ) return;
	TWeakObjectPtr<UChatConnection> connection = RoomData->GetConnection();
	if( !connection.IsValid() ) return;
	connection->SendCommand( FString::Printf( TEXT( "ST %d" ), RoomData->GetIndex() ) );
	RoomData->GetChatUi()->OnClickedTabChat();
}

void URoomListEntryInternal::OnClickedEnterButton()
{
	if( !RoomData ) return;
	TWeakObjectPtr<UChatConnection> connection = RoomData->GetConnection();
	if( !connection.IsValid() ) return;
	connection->SendCommand( FString::Printf( TEXT( "J %d" ), RoomData->GetIndex() ) );
	RoomData->GetChatUi()->OnClickedTabChat();
}

void URoomListEntryInternal::OnDataChanged()
{
	if( TextName ) TextName->SetText( FText::FromString( RoomData->GetTitle() ) );
	if( TextIndex ) TextIndex->SetText(
		FText::FromString(
			FString::Printf( TEXT( "%2d. " ), RoomData->GetIndex() )
		)
	);
	if( TextUser ) TextUser->SetText(
		FText::FromString(
			FString::Printf( TEXT( "(%2d/%2d)" ), RoomData->GetCurrentUserCount(), RoomData->GetMaxUserCount() )
		)
	);
}
