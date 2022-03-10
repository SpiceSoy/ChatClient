//=================================================================================================
// @file RoomListPage.h
//
// @brief 이용자 목록 UI 페이지를 위한 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserListPage.generated.h"


/**
 *
 */
UCLASS()
class CHATCLIENT_API UUserListPage : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UListView* ListViewUser;
public:
	void SetUserList( const TArray<class UUserData*>& arr ) const;
protected:
	virtual void NativeOnInitialized() override;
};
