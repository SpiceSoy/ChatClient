//=================================================================================================
// @file CommandQuitRoom.h
//
// @brief 대화방 종료를 위한 커맨드 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Command/BaseCommand.h"
#include "CoreMinimal.h"
#include "Containers/UnrealString.h"


class CHATCLIENT_API CommandQuitRoom : public BaseCommand
{
public:
	CommandQuitRoom(FCommandProcessor& processor);

	virtual ECommandStatus ProcessCommand(const FString& line) override;
};