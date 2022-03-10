// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "Containers/UnrealString.h"

class CHATCLIENT_API CommandQuitRoom : public BaseCommand
{
public:
	CommandQuitRoom(FCommandProcessor& processor);
	virtual ECommandStatus ProcessCommand(const FString& line);
};