//=================================================================================================
// @file RoomListEntry.h
//
// @brief 대화방 목록의 리스트뷰 내부 엔트리를 위한 클래스입니다.
//
// @date 2022/03/10
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "RoomListEntry.generated.h"


/**
 *
 */
UCLASS()
class CHATCLIENT_API URoomListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
private:
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class URoomListEntryInternal* roomListInternalWidget = nullptr;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet( UObject* listItemObject ) override;
	virtual void NativeOnItemSelectionChanged( bool isSelected ) override;
};
