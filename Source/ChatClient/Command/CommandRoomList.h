// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "Containers/UnrealString.h"

class CHATCLIENT_API CommandRoomList : public BaseCommand
{
public:
	CommandRoomList(FCommandProcessor& processor);
	virtual ECommandStatus ProcessCommand(const FString& line);
private:
	void ParseRoomData(const FString& line, int32& index, int32& currentUser, int32& maxUser, FString& title);
};