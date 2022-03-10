//=================================================================================================
// @file CommandRoomList.h
//
// @brief 대화방 목록을 파싱하기 위한 커맨드 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Command/BaseCommand.h"
#include "CoreMinimal.h"
#include "Containers/UnrealString.h"


class CHATCLIENT_API CommandRoomList : public BaseCommand
{
public:
	CommandRoomList(FCommandProcessor& processor);

	virtual ECommandStatus ProcessCommand(const FString& line) override;
private:
	void ParseRoomData(const FString& line, int32& index, int32& currentUser, int32& maxUser, FString& title);
};