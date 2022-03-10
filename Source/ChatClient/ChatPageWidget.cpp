// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatPageWidget.h"
#include "ChatPlayerController.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/RichTextBlock.h"
#include "Components/ScrollBox.h"

void UChatPageWidget::NativeOnInitialized()
{
	TextBoxLog = Cast<URichTextBlock>(GetWidgetFromName(TEXT("RTB_Log")));

	ScrollBoxChat = Cast<UScrollBox>(GetWidgetFromName(TEXT("SB_Chat")));

	TextBoxChat = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("TB_Chat")));
	TextBoxChat->OnTextCommitted.AddDynamic(this, &UChatPageWidget::OnTextCommittedChat);

	ButtonSend = Cast<UButton>(GetWidgetFromName(TEXT("BTN_Send")));
	ButtonSend->OnClicked.AddDynamic(this, &UChatPageWidget::OnClickedSend);
}

UChatPageWidget::FClickedSend& UChatPageWidget::GetClickedSend()
{
	return ClickedSend;
}

void UChatPageWidget::AppendLog(const FString& str) const
{
	FString newLog = TextBoxLog->GetText().ToString();
	newLog += str;
	TextBoxLog->SetText(FText::FromString(newLog));
	ScrollBoxChat->ScrollToEnd();
	UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::AppendLog"));
}

void UChatPageWidget::AppendLog(const FText& text) const
{
	AppendLog(text.ToString());
}

void UChatPageWidget::OnTextCommittedChat(const FText& text, ETextCommit::Type type)
{
	if (type == ETextCommit::Type::OnEnter)
	{
		OnClickedSend();
		TextBoxChat->SetUserFocus(this->GetOwningPlayer<AChatPlayerController>());
	}
	else if (type == ETextCommit::Type::OnCleared)
	{
		TextBoxChat->SetUserFocus(this->GetOwningPlayer<AChatPlayerController>());
	}
}

void UChatPageWidget::OnClickedSend()
{
	FString str = TextBoxChat->Text.ToString();
	if (str.Len() == 0) return;
	if (ClickedSend.IsBound()) ClickedSend.Execute(str);
	TextBoxChat->SetText(FText::GetEmpty());
}
