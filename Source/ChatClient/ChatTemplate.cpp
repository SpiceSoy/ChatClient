// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatTemplate.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"

void UChatTemplate::NativeOnInitialized()
{
	ButtonTabConnect = Cast<UButton>(GetWidgetFromName(TEXT("B_T_Connect")));
	ButtonTabConnect->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabConnect);

	ButtonTabChat = Cast<UButton>(GetWidgetFromName(TEXT("B_T_Chat")));
	ButtonTabChat->OnClicked.AddDynamic(this, &UChatTemplate::OnClickedTabChat);

	WidgetSwitcher = Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WS_Main")));
}

void UChatTemplate::OnClickedTabConnect()
{
	if(WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(0);
	UE_LOG(LogTemp, Display, TEXT("Clicked Connect"));
}

void UChatTemplate::OnClickedTabChat()
{
	if (WidgetSwitcher) WidgetSwitcher->SetActiveWidgetIndex(1);
	UE_LOG(LogTemp, Display, TEXT("Clicked Chat"));
}
