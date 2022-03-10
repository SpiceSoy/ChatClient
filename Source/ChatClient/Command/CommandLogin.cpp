//=================================================================================================
// @file CommandLoogin.cpp
//
// @brief 로그인 처리를 하기 위한 커맨드 클래스 입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandLogin.h"
#include "Command/CommandProcessor.h"


CommandLogin::CommandLogin(FCommandProcessor& processor)
	: BaseCommand(processor)
{

}

ECommandStatus CommandLogin::ProcessCommand(const FString& line)
{
	bool isStartLine = IsLineToken(line);
	if(isStartLine)
	{
		if(IsSameTitle(line, TEXT("로그인 성공")))
		{
			Processor.PostLoginComplete();
			return ECommandStatus::End;
		}

	}
	else if(line.StartsWith("**"))
	{
		 Processor.PostLoginFailed(line.Mid(2).TrimEnd());
		 return ECommandStatus::End;
	}
	return ECommandStatus::None;
}
