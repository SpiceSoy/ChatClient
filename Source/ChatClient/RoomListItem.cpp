// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomListItem.h"
#include "RoomData.h"
#include "Components/TextBlock.h"

constexpr const TCHAR* ID_TB_TITLE = TEXT("TB_Title");

void URoomListItem::NativeOnInitialized()
{
	TextName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_RoomName")));
	TextIndex = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Index")));
	TextUser = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_User")));
}

void URoomListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	URoomData* roomData = Cast<URoomData>(ListItemObject);
	if (TextName) TextName->SetText(FText::FromString(roomData->GetTitle()));
	if (TextIndex) TextIndex->SetText(
		FText::FromString(
			FString::Printf(TEXT("%2d. "), roomData->GetIndex())
		)
	);
	if (TextUser) TextUser->SetText(
		FText::FromString(
				FString::Printf(TEXT("(%2d/%2d)"), roomData->GetCurrentUserCount(), roomData->GetMaxUserCount())
			)
		);
}

void URoomListItem::NativeOnItemSelectionChanged(bool isSelected)
{
	if (isSelected)
	{
	}
	else
	{
	}
}
