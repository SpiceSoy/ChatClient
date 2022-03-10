// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandButton.h"
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
