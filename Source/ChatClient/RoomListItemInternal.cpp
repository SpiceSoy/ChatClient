// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomListItemInternal.h"
#include "RoomData.h"
#include "ChatConnection.h"
#include "ChatTemplate.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void URoomListItemInternal::Set(URoomData* roomData)
{
	RoomData = roomData;
	TWeakObjectPtr<URoomListItemInternal> thisObjPtr = MakeWeakObjectPtr(this);
	if (RoomData) RoomData->GetChangedData().BindLambda(
		[thisObjPtr]()
		{
			if(!thisObjPtr.IsValid()) return;
			URoomListItemInternal* thisPtr = thisObjPtr.Get();
			thisPtr->OnDataChanged();
		}
	);
	OnDataChanged();
}

void URoomListItemInternal::NativeOnInitialized()
{
	TextName = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_RoomName")));
	TextIndex = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_Index")));
	TextUser = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_User")));

	ButtonView = Cast<UButton>(GetWidgetFromName(TEXT("BTN_View")));
	ButtonView->OnClicked.AddDynamic(this, &URoomListItemInternal::OnClickedViewButton);
	ButtonEnter = Cast<UButton>(GetWidgetFromName(TEXT("BTN_Enter")));
	ButtonEnter->OnClicked.AddDynamic(this, &URoomListItemInternal::OnClickedEnterButton);
}

void URoomListItemInternal::NativeTick(const FGeometry& myGeometry, float inDeltaTime)
{

}


void URoomListItemInternal::OnClickedViewButton()
{
	if (!RoomData) return;
	TWeakObjectPtr<UChatConnection> connection = RoomData->GetConnection();
	if (!connection.IsValid()) return;
	connection->SendCommand(FString::Printf(TEXT("ST %d"), RoomData->GetIndex()));
	RoomData->GetChatUi()->OnClickedTabLobby();
}

void URoomListItemInternal::OnClickedEnterButton()
{
	if (!RoomData) return;
	TWeakObjectPtr<UChatConnection> connection = RoomData->GetConnection();
	if (!connection.IsValid()) return;
	connection->SendCommand(FString::Printf(TEXT("J %d"), RoomData->GetIndex()));
	RoomData->GetChatUi()->OnClickedTabLobby();
}

void URoomListItemInternal::OnDataChanged()
{
	if (TextName) TextName->SetText(FText::FromString(RoomData->GetTitle()));
	if (TextIndex) TextIndex->SetText(
		FText::FromString(
			FString::Printf(TEXT("%2d. "), RoomData->GetIndex())
		)
	);
	if (TextUser) TextUser->SetText(
		FText::FromString(
			FString::Printf(TEXT("(%2d/%2d)"), RoomData->GetCurrentUserCount(), RoomData->GetMaxUserCount())
		)
	);
}
