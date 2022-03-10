//=================================================================================================
// @file RoomListPage.h
//
// @brief 대화방 목록 UI 페이지를 위한 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomListPage.generated.h"


/**
 *
 */
UCLASS()
class CHATCLIENT_API URoomListPage : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UListView* ListViewRoom;

public:
	void SetRoomList( const TArray<class URoomData*>& arr );

protected:
	virtual void NativeOnInitialized() override;
};
