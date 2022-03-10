// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/UnrealString.h"

class FCommandProcessor;
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
	FCommandProcessor& Processor;
public:
	BaseCommand(FCommandProcessor& processor);
	virtual ~BaseCommand() = default;
	virtual ECommandStatus ProcessCommand(const FString& line) = 0;

	BaseCommand(const BaseCommand&) = delete;
	BaseCommand& operator=(const BaseCommand&) = delete;
protected:
	static bool IsLineToken(const FString& targetLine);
	static bool IsSameTitle(const FString& targetLine, const FString& predTitle);
};