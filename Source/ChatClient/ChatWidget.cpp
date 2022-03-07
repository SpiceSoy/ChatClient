// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWidget.h"
#include "Components/EditableTextBox.h"

#define ID_TB_IPADDRESS "TB_IPAddress"
#define ID_TB_PORT "TB_IPAddress"

void UChatWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextBoxIp = Cast<UEditableTextBox>(GetWidgetFromName(TEXT(ID_TB_IPADDRESS)));

	TextBoxPort = Cast<UEditableTextBox>(GetWidgetFromName(TEXT(ID_TB_PORT)));

	TextBoxIp->OnTextChanged.AddDynamic(this, &UChatWidget::OnTextChangedIpAddress);
	TextBoxPort->OnTextChanged.AddDynamic(this, &UChatWidget::OnTextChangedIpPort);
	UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::NativeOnInitialized"));

}

void UChatWidget::OnTextChangedIpAddress(const FText& text)
{
	FString newString = text.ToString();
	if (!newString.Right(0).IsNumeric())
	{
		newString = newString.Mid(0, newString.Len() - 1);
	}
	TextBoxIp->SetText(FText::FromString(newString));
	UE_LOG(LogTemp, Log, TEXT("CALL UChatWidget::OnTextChangedIpAddress"));
}

void UChatWidget::OnTextChangedIpPort(const FText& text)
{
	FString newString = text.ToString();
	if (!newString.Right(0).IsNumeric())
	{
		newString = newString.Mid(0, newString.Len() - 1);
	}
	TextBoxIp->SetText(FText::FromString(newString));
}
