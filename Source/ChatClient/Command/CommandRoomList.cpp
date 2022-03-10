//=================================================================================================
// @file CommandRoomList.cpp
//
// @brief 대화방 목록을 파싱하기 위한 커맨드 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandRoomList.h"
#include "Command/CommandProcessor.h"


CommandRoomList::CommandRoomList(FCommandProcessor& processor)
	: BaseCommand(processor)
{

}

ECommandStatus CommandRoomList::ProcessCommand(const FString& line)
{
	static bool isCurrentSet = false;
	bool isStartLine = IsLineToken(line);
	if (isCurrentSet)
	{
		if (isStartLine)
		{
			isCurrentSet = false;
			Processor.PostCompleteChangedOfRoomData();
			return ECommandStatus::End;
		}
		else
		{
			int32 index = 0;
			int32 currentUser = 0;
			int32 maxUser = 0;
			FString title;
			ParseRoomData(line, index, currentUser, maxUser, title);

			Processor.AddRoomList(index, title, currentUser, maxUser);
		}
	}
	else if (isStartLine)
	{
		if (IsSameTitle(line, TEXT("대화방 목록")))
		{
			isCurrentSet = true;
			Processor.PostStartChangedOfRoomData();
			return ECommandStatus::Processing;
		}

	}
	return ECommandStatus::None;
}

void CommandRoomList::ParseRoomData(const FString& line, int32& index, int32& currentUser, int32& maxUser, FString& title)
{
	static TArray<FString> tokens;
	int32 startTitle = 0;
	// 인덱스 파싱
	{
		int32 startIndex = 0;
		int32 endIndex = 0;
		line.FindChar(TEXT('['), startIndex);
		line.FindChar(TEXT(']'), endIndex);
		startIndex += 1;
		endIndex -= 1;
		FString indexString = line.Mid(startIndex, endIndex - startIndex + 1).TrimStartAndEnd();
		index = FCString::Atoi(*indexString);
	}
	// 유저카운트 파싱
	{
		int32 startIndex = 0;
		int32 endIndex = 0;
		line.FindChar(TEXT('('), startIndex);
		line.FindChar(TEXT(')'), endIndex);
		startIndex += 1;
		endIndex -= 1;
		FString userCountString = line.Mid(startIndex, endIndex - startIndex + 1).TrimStartAndEnd();

		tokens.Empty();
		const TCHAR* a = TEXT("/");
		userCountString.ParseIntoArray(tokens, &a, 1);

		currentUser = FCString::Atoi(*(tokens[0].TrimStartAndEnd()));
		maxUser = FCString::Atoi(*(tokens[1].TrimStartAndEnd()));

		startTitle = endIndex + 2;
	}
	// 타이틀 파싱
	{
		title = line.Mid(startTitle).TrimStartAndEnd();
	}
}
