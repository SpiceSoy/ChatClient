//=================================================================================================
// @file CommandQuitRoom.h
//
// @brief 대화방 종료를 위한 커맨드 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandQuitRoom.h"
#include "Command/CommandProcessor.h"


CommandQuitRoom::CommandQuitRoom(FCommandProcessor& processor)
	: BaseCommand(processor)
{

}

ECommandStatus CommandQuitRoom::ProcessCommand(const FString& line)
{
	bool isStartLine = IsLineToken(line);
	if(line.StartsWith("**"))
	{
		FString message = line.Mid(2).TrimStartAndEnd();
		if( message.StartsWith(TEXT("대화방에서 나갑니다.")))
		{
			Processor.PostExitedRoom();
			return ECommandStatus::End;
		}
	}
	return ECommandStatus::None;
}
