// Fill out your copyright notice in the Description page of Project Settings.


#include "UserListItem.h"
#include "UserData.h"
#include "Components/TextBlock.h"

constexpr const TCHAR* ID_TB_TITLE = TEXT("TB_Title");

void UUserListItem::NativeOnInitialized()
{
	Title = Cast<UTextBlock>(GetWidgetFromName(ID_TB_TITLE));
}

void UUserListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UUserData* userData = Cast<UUserData>(ListItemObject);
	Title->SetText(FText::FromString(userData->GetName()));
}

void UUserListItem::NativeOnItemSelectionChanged(bool isSelected)
{
	if(isSelected)
	{
	}
	else
	{
	}
}
