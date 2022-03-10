//=================================================================================================
// @file CommandEnterRoom.h
//
// @brief 대화방 입장 처리를 하기 위한 커맨드 클래스 입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "BaseCommand.h"
#include "Containers/UnrealString.h"
#include <CoreMinimal.h>


class CHATCLIENT_API CommandEnterRoom : public BaseCommand
{
public:
	CommandEnterRoom( FCommandProcessor& processor );

	virtual ECommandStatus ProcessCommand( const FString& line ) override;
};