//=================================================================================================
// @file UserListEntry.h
//
// @brief 이용자 목록 리스트뷰에 사용될 엔트리 UI 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Widget/UserListEntry.h"
#include "ChatConnection.h"
#include "UserData.h"
#include "Widget/ChatMainWidget.h"
#include "Widget/ChatPage.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


constexpr const TCHAR* ID_TB_TITLE = TEXT( "TB_Title" );

void UUserNameListEntry::NativeOnInitialized()
{
	TextBlockUserName = Cast<UTextBlock>( GetWidgetFromName( TEXT( "TB_UserName" ) ) );

	ButtonView = Cast<UButton>( GetWidgetFromName( TEXT( "BTN_View" ) ) );
	ButtonView->OnClicked.AddDynamic( this, &UUserNameListEntry::OnClickedButtonView );
	ButtonWhisper = Cast<UButton>( GetWidgetFromName( TEXT( "BTN_Whisper" ) ) );
	ButtonWhisper->OnClicked.AddDynamic( this, &UUserNameListEntry::OnClickedButtonWhisper );
	ButtonInvite = Cast<UButton>( GetWidgetFromName( TEXT( "BTN_Invite" ) ) );
	ButtonInvite->OnClicked.AddDynamic( this, &UUserNameListEntry::OnClickedButtonInvite );

}

void UUserNameListEntry::NativeOnListItemObjectSet( UObject* ListItemObject )
{
	UserData = Cast<UUserData>( ListItemObject );
	if( TextBlockUserName ) TextBlockUserName->SetText( FText::FromString( UserData->GetName() ) );
}

void UUserNameListEntry::NativeOnItemSelectionChanged( bool isSelected )
{

}

void UUserNameListEntry::OnClickedButtonView()
{
	if( !UserData ) return;
	TWeakObjectPtr<UChatConnection> connection = UserData->GetConnection();
	if( !connection.IsValid() ) return;
	connection->SendCommand( FString::Printf( TEXT( "PF %s" ), *UserData->GetName() ) );
	UserData->GetChatUi()->OnClickedTabChat();
}

void UUserNameListEntry::OnClickedButtonWhisper()
{
	if( !UserData ) return;
	TWeakObjectPtr<UChatConnection> connection = UserData->GetConnection();
	if( !connection.IsValid() ) return;
	UserData->GetChatUi()->GetChatPage()->SetChatInput( FString::Printf( TEXT( "TO %s " ), *UserData->GetName() ) );
	UserData->GetChatUi()->OnClickedTabChat();
	UserData->GetChatUi()->GetChatPage()->FocusChatInput();
}

void UUserNameListEntry::OnClickedButtonInvite()
{
	if( !UserData ) return;
	TWeakObjectPtr<UChatConnection> connection = UserData->GetConnection();
	if( !connection.IsValid() ) return;
	connection->SendCommand( FString::Printf( TEXT( "IN %s" ), *UserData->GetName() ) );
	UserData->GetChatUi()->OnClickedTabChat();
}
