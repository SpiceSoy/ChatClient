//=================================================================================================
// @file CommandButton.cpp
//
// @brief 명령어 버튼을 위한 람다 함수 등록 버튼 클래스 입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Widget/CommandButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"


constexpr const TCHAR* ID_TB_TITLE = TEXT("TB_Title");
constexpr const TCHAR* ID_B_BUTTON = TEXT("B_Button");


void UCommandButton::SetFuctor(const std::function<void()>& functor)
{
	Functor = functor;
}

void UCommandButton::SetTitle(const FString& title)
{
	if(Title) Title->SetText(FText::FromString(title));
}

void UCommandButton::Set(const FString& title, const std::function<void()>& functor)
{
	SetTitle(title);
	SetFuctor(functor);
}

void UCommandButton::NativeOnInitialized()
{
	Button = Cast<UButton>(GetWidgetFromName(ID_B_BUTTON));
	Button->OnClicked.AddDynamic(this, &UCommandButton::CallFuntor);

	Title = Cast<UTextBlock>(GetWidgetFromName(ID_TB_TITLE));
}

void UCommandButton::CallFuntor()
{
	if(Functor) Functor();
}
