// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandProcessor.h"
#include "CommandUserList.h"
#include "BaseCommand.h"

FCommandProcessor::FCommandProcessor()
{
	Commands.Add(MakeUnique<CommandUserList>(*this));
}

FCommandProcessor::~FCommandProcessor()
{
}

void FCommandProcessor::PostStartChangedOfUserData()
{
	UserDatas.Empty();
}

void FCommandProcessor::AddUserList(const FString& name, const FString& addr)
{
	int32 newIndex = UserDatas.Num();
	if(newIndex <= UserDataPool.Num())
	{
		UserDataPool.Emplace(NewObject<UUserData>());
	}
	UUserData* ptr = UserDataPool[newIndex];
	ptr->Set(name, addr);
	UserDatas.Add(ptr);
}

void FCommandProcessor::PostCompleteChangedOfUserData()
{
	if(ChangedUserList.IsBound()) ChangedUserList.Execute(UserDatas);
}

FCommandProcessor::FChangedUserList& FCommandProcessor::GetChangedUserList()
{
	return ChangedUserList;
}

bool FCommandProcessor::ProcessLine(const FString& line)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *line);
	bool hasCurrentCmd = CurrentCommand != NO_COMMAND;
	int32 i = hasCurrentCmd ? CurrentCommand : 0;
	int32 maxCommand = hasCurrentCmd ? CurrentCommand + 1 : Commands.Num();

	while (i < maxCommand)
	{
		BaseCommand* ptr = Commands[i].Get();
		ECommandStatus result = ptr->ProcessCommand(line);
		if (result == ECommandStatus::Processing)
		{
			CurrentCommand = i;
			return true;
		}
		else if (result == ECommandStatus::End)
		{
			CurrentCommand = NO_COMMAND;
			return true;
		}
		else // ECommandStatus::None
		{
			i++;
		}
	}
	return true;
}