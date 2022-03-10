// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCommand.h"

BaseCommand::BaseCommand(FCommandProcessor& processor)
	: Processor(processor)
{

}

bool BaseCommand::IsLineToken(const FString& targetLine)
{
	return targetLine.StartsWith(TEXT("--------------------"));
}

bool BaseCommand::IsSameTitle(const FString& targetLine, const FString& predTitle)
{
	int32 startIndex = 0;
	int32 endIndex = 0;
	bool isTitle = targetLine.FindChar(TEXT('['), startIndex) && targetLine.FindChar(TEXT(']'), endIndex);
	if(!isTitle) return false;
	startIndex += 1;
	endIndex -= 1;
	FString titleResult = targetLine.Mid(startIndex, endIndex - startIndex + 1).TrimStartAndEnd();
	return titleResult == predTitle;
}
