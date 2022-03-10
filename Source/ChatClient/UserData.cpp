//=================================================================================================
// @file UserData.h
//
// @brief 이용자 목록 공유를 위한 대화방 정보 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "UserData.h"
#include "ChatConnection.h"
#include "ChatTemplate.h"


UUserData::UUserData()
	: UObject()
{
	Set( ERROR_NAME, ERROR_ADDR );
}

void UUserData::Set( const FString& name, const FString address )
{
	Name = name;
	Address = address;
}

void UUserData::SetPtr( const TWeakObjectPtr<UChatConnection>& connection, const TWeakObjectPtr<UChatTemplate>& chatUi )
{
	Connection = connection;
	ChatUi = chatUi;
}

const FString& UUserData::GetName() const
{
	return Name;
}

const FString& UUserData::GetAddress() const
{
	return Address;
}

const TWeakObjectPtr<UChatConnection>& UUserData::GetConnection() const
{
	return Connection;
}

const TWeakObjectPtr<UChatTemplate>& UUserData::GetChatUi() const
{
	return ChatUi;
}
