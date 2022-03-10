// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandLogin.h"
#include "CommandProcessor.h"

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
