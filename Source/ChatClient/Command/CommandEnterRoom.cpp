//=================================================================================================
// @file CommandEnterRoom.cpp
//
// @brief 대화방 입장 처리를 하기 위한 커맨드 클래스 입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/CommandEnterRoom.h"
#include "Command/CommandProcessor.h"


CommandEnterRoom::CommandEnterRoom( FCommandProcessor& processor )
	: BaseCommand( processor )
{

}

ECommandStatus CommandEnterRoom::ProcessCommand( const FString& line )
{
	bool isStartLine = IsLineToken( line );
	if( line.StartsWith( "**" ) )
	{
		FString message = line.Mid( 2 ).TrimStartAndEnd();
		bool isTargetCommand = message.StartsWith( TEXT( "대화방에 들어갑니다." ) ) || message.StartsWith( TEXT( "대화방이 개설되었습니다." ) );
		if( isTargetCommand )
		{
			Processor.PostEnteredRoom();
			return ECommandStatus::End;
		}
	}
	return ECommandStatus::None;
}
