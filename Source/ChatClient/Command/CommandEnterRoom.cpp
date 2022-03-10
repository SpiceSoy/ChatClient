// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandEnterRoom.h"
#include "CommandProcessor.h"

CommandEnterRoom::CommandEnterRoom(FCommandProcessor& processor)
	: BaseCommand(processor)
{

}

ECommandStatus CommandEnterRoom::ProcessCommand(const FString& line)
{
	bool isStartLine = IsLineToken(line);
	if (line.StartsWith("**"))
	{
		FString message = line.Mid(2).TrimStartAndEnd();
		if (message.StartsWith(TEXT("대화방에 들어갑니다.")) || message.StartsWith(TEXT("대화방이 개설되었습니다.")))
		{
			Processor.PostEnteredRoom();
			return ECommandStatus::End;
		}
	}
	return ECommandStatus::None;
}
