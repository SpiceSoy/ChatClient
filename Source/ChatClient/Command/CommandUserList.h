//=================================================================================================
// @file CommandUserList.h
//
// @brief 이용자 목록을 파싱하기 위한 커맨드 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Command/BaseCommand.h"
#include "CoreMinimal.h"
#include "Containers/UnrealString.h"


class CHATCLIENT_API CommandUserList : public BaseCommand
{
public:
	CommandUserList(FCommandProcessor& processor);

	virtual ECommandStatus ProcessCommand(const FString& line) override;
};