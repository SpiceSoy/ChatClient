//=================================================================================================
// @file CommandRoomList.cpp
//
// @brief 대화방 목록을 파싱하기 위한 커맨드 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandUserList.h"
#include "Command/CommandProcessor.h"


CommandUserList::CommandUserList(FCommandProcessor& processor)
	: BaseCommand(processor)
{

}

ECommandStatus CommandUserList::ProcessCommand(const FString& line)
{
	static bool isCurrentSet = false;
	static TArray<FString> tokens;
	bool isStartLine = IsLineToken(line);
	if(isCurrentSet)
	{
		if(isStartLine)
		{
			isCurrentSet = false;
			Processor.PostCompleteChangedOfUserData();
			return ECommandStatus::End;
		}
		else
		{
			tokens.Empty();
			const TCHAR* a = TEXT(" ");
			line.ParseIntoArray(tokens, &a, 1);
			Processor.AddUserList(tokens[1], tokens[3]);
		}
	}
	else if(isStartLine)
	{
		if(IsSameTitle(line, TEXT("이용자 목록")))
		{
			isCurrentSet = true;
			Processor.PostStartChangedOfUserData();
			return ECommandStatus::Processing;
		}

	}
	return ECommandStatus::None;
}
