//=================================================================================================
// @file BaseCommand.cpp
//
// @brief 커맨드 파싱, 처리를 하기 위한 커맨드 클래스들의 부모 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#include "Command/BaseCommand.h"


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
	if (!isTitle) return false;
	startIndex += 1;
	endIndex -= 1;
	FString titleResult = targetLine.Mid(startIndex, endIndex - startIndex + 1).TrimStartAndEnd();
	return titleResult == predTitle;
}
