// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandQuitRoom.h"
#include "CommandProcessor.h"

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
