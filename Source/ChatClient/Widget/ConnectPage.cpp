//=================================================================================================
// @file ChatConnection.h
//
// @brief 채팅 서버와 소켓 통신을 하기 위한 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Widget/ConnectPage.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Networking.h"

void UConnectPage::NativeOnInitialized()
{
	TextBoxIp = Cast<UEditableTextBox>( GetWidgetFromName( TEXT( "TB_IPAddress" ) ) );
	TextBoxIp->OnTextChanged.AddDynamic( this, &UConnectPage::OnChangedIpText );

	TextBoxPort = Cast<UEditableTextBox>( GetWidgetFromName( TEXT( "TB_Port" ) ) );
	TextBoxPort->OnTextChanged.AddDynamic( this, &UConnectPage::OnChangedPortText );

	TextBoxName = Cast<UEditableTextBox>( GetWidgetFromName( TEXT( "TB_Name" ) ) );

	ButtonConnect = Cast<UButton>( GetWidgetFromName( TEXT( "BTN_Connect" ) ) );
	ButtonConnect->OnClicked.AddDynamic( this, &UConnectPage::OnClickedConnectBtn );

	ButtonLogin = Cast<UButton>( GetWidgetFromName( TEXT( "BTN_Login" ) ) );
	ButtonLogin->OnClicked.AddDynamic( this, &UConnectPage::OnClickedChatLoginBtn );

	TextBlockConnect = Cast<UTextBlock>( GetWidgetFromName( TEXT( "T_Info" ) ) );
}

UConnectPage::FClickedConnectBtn& UConnectPage::GetClickedConnectBtn()
{
	return ClickedConnectBtn;
}

UConnectPage::FClickedLoginBtn& UConnectPage::GetClickedLoginBtn()
{
	return ClickedLoginBtn;
}

void UConnectPage::SetConnectionInfoText( const FString& text )
{
	if( TextBlockConnect ) TextBlockConnect->SetText( FText::FromString( text ) );
}

void UConnectPage::OnClickedConnectBtn()
{
	UE_LOG( LogTemp, Log, TEXT( "CALL UChatWidget::OnConnectBtnPressed" ) );
	FString addressString = TextBoxIp->GetText().ToString();
	FString portString = TextBoxPort->GetText().ToString();

	FIPv4Address ipAddr;
	bool result = FIPv4Address::Parse( addressString, ipAddr );
	if( result )
	{
		uint32 address = ipAddr.Value;
		uint32 portNum = FCString::Atoi( *portString );
		if( ClickedConnectBtn.IsBound() ) ClickedConnectBtn.Execute( address, portNum );
	}
	else
	{
		SetConnectionInfoText( TEXT( "주소 형식이 이상합니다.\n" ) );
	}
}

void UConnectPage::OnClickedChatLoginBtn()
{
	if( !TextBoxName ) return;
	FString str = TextBoxName->GetText().ToString();
	if( str.IsEmpty() ) return;
	if( ClickedLoginBtn.IsBound() ) ClickedLoginBtn.Execute( str );
}

void UConnectPage::OnChangedIpText( const FText& text )
{
	FString newString = text.ToString();
	if( newString.IsEmpty() ) return;
	FString lastInput = newString.Right( 1 );
	TArray<TCHAR> scores = newString.GetCharArray().FilterByPredicate( [] ( const CHAR a ) {return a == TEXT( '.' ); } );
	bool lastInputIsIpElement = lastInput.IsNumeric() || lastInput[ 0 ] == TEXT( '.' );
	bool dotCountIsValid = lastInput[ 0 ] != TEXT( '.' ) || scores.Num() < 4;
	if( !( lastInputIsIpElement && dotCountIsValid ) )
	{
		newString = newString.Mid( 0, newString.Len() - 1 );
	}
	TextBoxIp->SetText( FText::FromString( newString ) );
	UE_LOG( LogTemp, Log, TEXT( "CALL UChatWidget::OnTextChangedIpAddress" ) );
}

void UConnectPage::OnChangedPortText( const FText& text )
{
	FString newString = text.ToString();
	if( newString.IsEmpty() ) return;
	if( !newString.IsNumeric() )
	{
		newString = newString.Mid( 0, newString.Len() - 1 );
	}
	TextBoxPort->SetText( FText::FromString( newString ) );
}
