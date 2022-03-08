//=================================================================================================
// @file UChatWidget.cpp
//
// @brief Custom widget for chatting client
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "ChatWidget.h"
#include "ChatPlayerController.h"
#include "Networking.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/RichTextBlock.h"
#include "Components/ScrollBox.h"

#define ID_TB_IPADDRESS "TB_IPAddress"
#define ID_TB_PORT "TB_Port"
#define ID_TB_CHAT "TB_Chat"
#define ID_RTB_LOG "RTB_Log"
#define ID_BTN_CONNECT "BTN_Connect"
#define ID_BTN_SEND "BTN_Send"
#define ID_SB_CHAT "SB_Chat"

UChatWidget::FConnectBtnPressed& UChatWidget::GetConnectBtnPressed()
{
	return ConnectBtnPressed;
}

UChatWidget::FChatSendBtnPressed& UChatWidget::GetChatSendBtnPressed()
{
	return ChatSendBtnPressed;
}

void UChatWidget::AppendLog(const FString& str) const
{
	FString newLog = TextBoxLog->GetText().ToString();
	newLog += str;
	TextBoxLog->SetText(FText::FromString(newLog));
	ScrollBoxChat->ScrollToEnd();
	UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::AppendLog"));
}

void UChatWidget::AppendLog(const FText& text) const
{
	AppendLog(text.ToString());
}

void UChatWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextBoxIp = Cast<UEditableTextBox>(GetWidgetFromName(TEXT(ID_TB_IPADDRESS)));
	TextBoxPort = Cast<UEditableTextBox>(GetWidgetFromName(TEXT(ID_TB_PORT)));
	TextBoxChat = Cast<UEditableTextBox>(GetWidgetFromName(TEXT(ID_TB_CHAT)));
	TextBoxLog = Cast<URichTextBlock>(GetWidgetFromName(TEXT(ID_RTB_LOG)));
	ConnectButton = Cast<UButton>(GetWidgetFromName(TEXT(ID_BTN_CONNECT)));
	SendButton = Cast<UButton>(GetWidgetFromName(TEXT(ID_BTN_SEND)));
	ScrollBoxChat = Cast<UScrollBox>(GetWidgetFromName(TEXT(ID_SB_CHAT)));

	TextBoxIp->OnTextChanged.AddDynamic(this, &UChatWidget::OnTextChangedIpAddress);
	TextBoxPort->OnTextChanged.AddDynamic(this, &UChatWidget::OnTextChangedIpPort);
	TextBoxChat->OnTextCommitted.AddDynamic(this, &UChatWidget::OnChatCommitted);
	ConnectButton->OnClicked.AddDynamic(this, &UChatWidget::OnConnectBtnPressed);
	SendButton->OnClicked.AddDynamic(this, &UChatWidget::OnChatSendBtnPressed);

	UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::NativeOnInitialized"));

}

void UChatWidget::OnTextChangedIpAddress(const FText& text)
{
	FString newString = text.ToString();
	if (newString.IsEmpty()) return;
	FString lastInput = newString.Right(1);
	TArray<TCHAR> scores = newString.GetCharArray().FilterByPredicate([](const CHAR a) {return a == TEXT('.'); });
	bool lastInputIsIpElement = lastInput.IsNumeric() || lastInput[0] == TEXT('.');
	bool dotCountIsValid = lastInput[0] != TEXT('.') || scores.Num() < 4;
	if (!(lastInputIsIpElement && dotCountIsValid))
	{
		newString = newString.Mid(0, newString.Len() - 1);
	}
	TextBoxIp->SetText(FText::FromString(newString));
	UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::OnTextChangedIpAddress"));
}

void UChatWidget::OnTextChangedIpPort(const FText& text)
{
	FString newString = text.ToString();
	if(newString.IsEmpty()) return;
	if (!newString.IsNumeric())
	{
		newString = newString.Mid(0, newString.Len() - 1);
	}
	TextBoxPort->SetText(FText::FromString(newString));
}

void UChatWidget::OnConnectBtnPressed()
{
	UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::OnConnectBtnPressed"));
	FString addressString = TextBoxIp->GetText().ToString();
	FString portString = TextBoxPort->GetText().ToString();

	FIPv4Address ipAddr;
	bool result = FIPv4Address::Parse(addressString, ipAddr);
	if (result)
	{
		uint32 address = ipAddr.Value;
		uint32 portNum = FCString::Atoi(*portString);
		ConnectBtnPressed.Execute(address, portNum);
	}
	else 
	{
		AppendLog(TEXT("Address is Wrong\n"));
	}
}

void UChatWidget::OnChatSendBtnPressed()
{
	UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::OnChatSendBtnPressed"));
	FString str = TextBoxChat->Text.ToString();
	if (str.Len() == 0) return;
	ChatSendBtnPressed.Execute(str);
	TextBoxChat->SetText(FText::GetEmpty());
}

void UChatWidget::OnChatCommitted(const FText& text, ETextCommit::Type type)
{
	if(type == ETextCommit::Type::OnEnter)
	{
		OnChatSendBtnPressed();
		TextBoxChat->SetUserFocus(this->GetOwningPlayer<AChatPlayerController>());
		UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::SetKeyboardFocus"));
	}
	else if(type == ETextCommit::Type::OnCleared)
	{
		TextBoxChat->SetUserFocus(this->GetOwningPlayer<AChatPlayerController>());
	}
}

