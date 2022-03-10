// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatPageWidget.h"
#include "ChatPlayerController.h"
#include "CommandButton.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/RichTextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UChatPageWidget::NativeOnInitialized()
{
	TextBoxLog = Cast<URichTextBlock>(GetWidgetFromName(TEXT("RTB_Log")));

	ScrollBoxChat = Cast<UScrollBox>(GetWidgetFromName(TEXT("SB_Chat")));

	TextTitle = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_CurrentInRoom")));

	TextBoxChat = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("TB_Chat")));
	TextBoxChat->OnTextCommitted.AddDynamic(this, &UChatPageWidget::OnTextCommittedChat);

	ButtonSend = Cast<UButton>(GetWidgetFromName(TEXT("BTN_Send")));
	ButtonSend->OnClicked.AddDynamic(this, &UChatPageWidget::OnClickedSend);

	VerticalBoxCommand = Cast<UVerticalBox>(GetWidgetFromName(TEXT("VB_Command")));

	if(ClassCommandButton)
	{
		TWeakObjectPtr< UChatPageWidget > thisObjPtr = MakeWeakObjectPtr(this);

		auto CommandButtonGenerator = [this, thisObjPtr](const FString& buttonText, const FString& commandText){
			UCommandButton* button = CreateWidget<UCommandButton>(this->GetOwningPlayer(), ClassCommandButton);
			if (button)
			{
				button->Set(buttonText,
					[thisObjPtr, commandText]()
					{
						if (!thisObjPtr.IsValid()) return;
						UChatPageWidget* chatWidget = thisObjPtr.Get();
						chatWidget->SetChatInput(chatWidget->GetCommandPrefix() + commandText);
					}
				);
				VerticalBoxCommand->AddChild(button);
			}
			return button;
		};
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("명령어 안내"), TEXT("H"))
		);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("이용자 목록 보기"), TEXT("US"))
			);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("대화방 목록 보기"), TEXT("LT"))
			);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("대화방 정보 보기"), TEXT("ST [방번호]"))
			);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("이용자 정보 보기"), TEXT("PF [상대방ID]"))
			);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("쪽지 보내기"), TEXT("TO [상대방ID] [메시지]"))
			);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("대화방 만들기"), TEXT("O [최대인원] [방제목]"))
			);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("초대 메시지 보내기"), TEXT("IN [상대방ID]"))
			);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("대화방 나가기"), TEXT("Q"))
			);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("대화방 들어가기"), TEXT("J [방번호]"))
		);
		CommandButtons.Add(
			CommandButtonGenerator(TEXT("끝내기"), TEXT("X"))
			);
	}
	SetChatRoom(false);
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

void UChatPageWidget::SetChatInput(const FString& str) const
{
	if(!TextBoxChat) return;
	TextBoxChat->SetText(FText::FromString(str));
}

void UChatPageWidget::FocusChatInput() const
{
	if (!TextBoxChat) return;
	TextBoxChat->SetUserFocus(this->GetOwningPlayer<AChatPlayerController>());
}

void UChatPageWidget::SetChatRoom(bool isInRoom)
{
	IsInRoom = isInRoom;
	ESlateVisibility inRoom = IsInRoom ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	ESlateVisibility inLobby = IsInRoom ? ESlateVisibility::Collapsed : ESlateVisibility::Visible;
	FString title = IsInRoom ? TEXT("대화방") : TEXT("로비");

	CommandButtons[7]->SetVisibility(inRoom);
	CommandButtons[8]->SetVisibility(inRoom);
	CommandButtons[9]->SetVisibility(inLobby);
	if(TextTitle) TextTitle->SetText(FText::FromString(title));
}

const FString& UChatPageWidget::GetCommandPrefix() const
{
	static FString command = TEXT("/");
	static FString noCommand = TEXT("");
	if(IsInRoom) return command;
	else return noCommand;
}

void UChatPageWidget::OnTextCommittedChat(const FText& text, ETextCommit::Type type)
{
	if (type == ETextCommit::Type::OnEnter)
	{
		OnClickedSend();
		FocusChatInput();
	}
	else if (type == ETextCommit::Type::OnCleared)
	{
		FocusChatInput();
	}
}

void UChatPageWidget::OnClickedSend()
{
	FString str = TextBoxChat->Text.ToString();
	if (str.Len() == 0) return;
	if (ClickedSend.IsBound()) ClickedSend.Execute(str);
	TextBoxChat->SetText(FText::GetEmpty());
}
