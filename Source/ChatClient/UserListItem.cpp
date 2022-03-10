// Fill out your copyright notice in the Description page of Project Settings.


#include "UserListItem.h"
#include "UserData.h"
#include "ChatTemplate.h"
#include "ChatConnection.h"
#include "ChatPageWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

constexpr const TCHAR* ID_TB_TITLE = TEXT("TB_Title");

void UUserListItem::NativeOnInitialized()
{
	TextBlockUserName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_UserName")));

	ButtonView = Cast<UButton>(GetWidgetFromName(TEXT("BTN_View")));
	ButtonView->OnClicked.AddDynamic(this, &UUserListItem::OnClickedButtonView);
	ButtonWhisper = Cast<UButton>(GetWidgetFromName(TEXT("BTN_Whisper")));
	ButtonWhisper->OnClicked.AddDynamic(this, &UUserListItem::OnClickedButtonWhisper);
	ButtonInvite = Cast<UButton>(GetWidgetFromName(TEXT("BTN_Invite")));
	ButtonInvite->OnClicked.AddDynamic(this, &UUserListItem::OnClickedButtonInvite);

}

void UUserListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UserData = Cast<UUserData>(ListItemObject);
	if(TextBlockUserName) TextBlockUserName->SetText(FText::FromString(UserData->GetName()));
}

void UUserListItem::NativeOnItemSelectionChanged(bool isSelected)
{

}

void UUserListItem::OnClickedButtonView()
{
	if (!UserData) return;
	TWeakObjectPtr<UChatConnection> connection = UserData->GetConnection();
	if (!connection.IsValid()) return;
	connection->SendCommand(FString::Printf(TEXT("PF %s"), *UserData->GetName()));
	UserData->GetChatUi()->OnClickedTabLobby();
}

void UUserListItem::OnClickedButtonWhisper()
{
	if (!UserData) return;
	TWeakObjectPtr<UChatConnection> connection = UserData->GetConnection();
	if (!connection.IsValid()) return;
	UserData->GetChatUi()->GetLobbyWidget()->SetChatInput(FString::Printf(TEXT("TO %s "), *UserData->GetName()));
	UserData->GetChatUi()->OnClickedTabLobby();
	UserData->GetChatUi()->GetLobbyWidget()->FocusChatInput();
}

void UUserListItem::OnClickedButtonInvite()
{
	if (!UserData) return;
	TWeakObjectPtr<UChatConnection> connection = UserData->GetConnection();
	if (!connection.IsValid()) return;
	connection->SendCommand(FString::Printf(TEXT("IN %s"), *UserData->GetName()));
	UserData->GetChatUi()->OnClickedTabLobby();
}
