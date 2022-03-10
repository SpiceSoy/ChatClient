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
#include "CommandButton.h"
#include "Networking.h"
#include "UserData.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "Components/RichTextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"

constexpr const TCHAR* ID_TB_IPADDRESS = TEXT("TB_IPAddress");
constexpr const TCHAR* ID_TB_PORT = TEXT("TB_Port");
constexpr const TCHAR* ID_TB_CHAT = TEXT("TB_Chat");
constexpr const TCHAR* ID_RTB_LOG = TEXT("RTB_Log");
constexpr const TCHAR* ID_BTN_CONNECT = TEXT("BTN_Connect");
constexpr const TCHAR* ID_BTN_SEND = TEXT("BTN_Send");
constexpr const TCHAR* ID_SB_CHAT = TEXT("SB_Chat");
constexpr const TCHAR* ID_B_C_HELP = TEXT("B_C_Help");
constexpr const TCHAR* ID_B_C_QUIT = TEXT("B_C_Quit");
constexpr const TCHAR* ID_B_C_USERLIST = TEXT("B_C_UserList");
constexpr const TCHAR* ID_B_C_ROOMLIST = TEXT("B_C_RoomList");
constexpr const TCHAR* ID_WB_COMMAND = TEXT("WB_Command");
constexpr const TCHAR* ID_LV_USER = TEXT("LV_User");

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

void UChatWidget::SetUserList(const TArray<class UUserData*>& arr) const
{
	ListViewUser->SetListItems(arr);
}

void UChatWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextBoxIp = Cast<UEditableTextBox>(GetWidgetFromName(ID_TB_IPADDRESS));
	TextBoxIp->OnTextChanged.AddDynamic(this, &UChatWidget::OnTextChangedIpAddress);

	TextBoxPort = Cast<UEditableTextBox>(GetWidgetFromName(ID_TB_PORT));
	TextBoxPort->OnTextChanged.AddDynamic(this, &UChatWidget::OnTextChangedIpPort);

	TextBoxChat = Cast<UEditableTextBox>(GetWidgetFromName(ID_TB_CHAT));
	TextBoxChat->OnTextCommitted.AddDynamic(this, &UChatWidget::OnChatCommitted);

	TextBoxLog = Cast<URichTextBlock>(GetWidgetFromName(ID_RTB_LOG));

	ConnectButton = Cast<UButton>(GetWidgetFromName(ID_BTN_CONNECT));
	ConnectButton->OnClicked.AddDynamic(this, &UChatWidget::OnConnectBtnPressed);

	SendButton = Cast<UButton>(GetWidgetFromName(ID_BTN_SEND));
	SendButton->OnClicked.AddDynamic(this, &UChatWidget::OnChatSendBtnPressed);

	ScrollBoxChat = Cast<UScrollBox>(GetWidgetFromName(ID_SB_CHAT));

	WrapBoxCommand = Cast<UWrapBox>(GetWidgetFromName(ID_WB_COMMAND));

	ListViewUser = Cast<UListView>(GetWidgetFromName(ID_LV_USER));

	TWeakObjectPtr< UChatWidget > thisObjPtr(this);
	if (ClassCommandButton)
	{

	}


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
	if (newString.IsEmpty()) return;
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
		if(ConnectBtnPressed.IsBound()) ConnectBtnPressed.Execute(address, portNum);
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
	if (ChatSendBtnPressed.IsBound()) ChatSendBtnPressed.Execute(str);
	TextBoxChat->SetText(FText::GetEmpty());
}

void UChatWidget::OnChatCommitted(const FText& text, ETextCommit::Type type)
{
	if (type == ETextCommit::Type::OnEnter)
	{
		OnChatSendBtnPressed();
		TextBoxChat->SetUserFocus(this->GetOwningPlayer<AChatPlayerController>());
		UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::SetKeyboardFocus"));
	}
	else if (type == ETextCommit::Type::OnCleared)
	{
		TextBoxChat->SetUserFocus(this->GetOwningPlayer<AChatPlayerController>());
	}
}

