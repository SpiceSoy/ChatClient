//=================================================================================================
// @file BaseCommand.h
//
// @brief 커맨드 파싱, 처리를 하기 위한 커맨드 클래스들의 부모 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================

#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"

enum class ECommandStatus
{
	None,
	Processing,
	End
};

/**
 *
 */
class CHATCLIENT_API BaseCommand
{
protected:
	class FCommandProcessor& Processor;
public:
	BaseCommand( FCommandProcessor& processor );
	virtual ~BaseCommand() = default;

	BaseCommand( const BaseCommand& ) = delete;
	BaseCommand& operator=( const BaseCommand& ) = delete;

	virtual ECommandStatus ProcessCommand( const FString& line ) = 0;
protected:
	static bool IsLineToken( const FString& targetLine );
	static bool IsSameTitle( const FString& targetLine, const FString& predTitle );
};