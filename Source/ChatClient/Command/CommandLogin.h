//=================================================================================================
// @file CommandLoogin.h
//
// @brief 로그인 처리를 하기 위한 커맨드 클래스 입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "Containers/UnrealString.h"


class CHATCLIENT_API CommandLogin : public BaseCommand
{
public:
	CommandLogin(FCommandProcessor& processor);

	virtual ECommandStatus ProcessCommand(const FString& line) override;
};