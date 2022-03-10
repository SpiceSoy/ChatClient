//=================================================================================================
// @file RoomData.h
//
// @brief 대화방 목록 공유를 위한 대화방 정보 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoomData.generated.h"


/**
 * 
 */
UCLASS()
class CHATCLIENT_API URoomData : public UObject
{
	GENERATED_BODY()
	DECLARE_DELEGATE(FChangedData);
private:
	int32 Index;
	int32 CurrentUserCount;
	int32 MaxUserCount;
	FString Title;
	TWeakObjectPtr<class UChatConnection> Connection;
	TWeakObjectPtr<class UChatTemplate> ChatUi;
	FChangedData ChangedData;
	constexpr static int32 ERROR_NUM = 9393939393;
	constexpr static FString ERROR_TITLE = TEXT("ERROR_ROOM");
public:
	URoomData();
	virtual ~URoomData() = default;

	void Set(int32 index, const FString& title, int32 currentUserCount, int32 maxUserCount);
	void SetPtr(const TWeakObjectPtr<UChatConnection>& connection, const TWeakObjectPtr<UChatTemplate>& chatUi);

	const FString& GetTitle() const;
	int32 GetIndex() const;
	int32 GetMaxUserCount() const;
	int32 GetCurrentUserCount() const;
	FChangedData& GetChangedData();
	const TWeakObjectPtr<UChatConnection>& GetConnection() const;
	const TWeakObjectPtr<UChatTemplate>& GetChatUi() const;
};
