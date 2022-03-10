// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandUserList.h"
#include "CommandProcessor.h"

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
