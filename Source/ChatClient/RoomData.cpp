//=================================================================================================
// @file RoomData.h
//
// @brief 대화방 목록 공유를 위한 대화방 정보 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "RoomData.h"
#include "ChatConnection.h"


URoomData::URoomData()
	: UObject()
{
	Set( ERROR_NUM, ERROR_TITLE, ERROR_NUM, ERROR_NUM );
}

void URoomData::Set( int32 index, const FString& title, int32 currnet, int32 max )
{
	Index = index;
	Title = title;
	CurrentUserCount = currnet;
	MaxUserCount = max;
	ChangedData.ExecuteIfBound();
}

void URoomData::SetPtr( const TWeakObjectPtr<class UChatConnection>& connection, const TWeakObjectPtr<class UChatMainWidget>& chatUi )
{
	Connection = connection;
	ChatUi = chatUi;
}

const FString& URoomData::GetTitle() const
{
	return Title;
}

int32 URoomData::GetIndex() const
{
	return Index;
}

int32 URoomData::GetCurrentUserCount() const
{
	return CurrentUserCount;
}

int32 URoomData::GetMaxUserCount() const
{
	return MaxUserCount;
}

const TWeakObjectPtr<class UChatConnection>& URoomData::GetConnection() const
{
	return Connection;
}

const TWeakObjectPtr<class UChatMainWidget>& URoomData::GetChatUi() const
{
	return ChatUi;
}

URoomData::FChangedData& URoomData::GetChangedData()
{
	return ChangedData;
}
