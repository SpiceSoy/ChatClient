// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandProcessor.h"
#include "CommandEnterRoom.h"
#include "CommandLogin.h"
#include "CommandQuitRoom.h"
#include "CommandRoomList.h"
#include "CommandUserList.h"
#include "BaseCommand.h"

FCommandProcessor::FCommandProcessor()
{
	loginCommand = MakeUnique<CommandLogin>(*this);

	Commands.Add(MakeUnique<CommandUserList>(*this));
	Commands.Add(MakeUnique<CommandRoomList>(*this));
	Commands.Add(MakeUnique<CommandEnterRoom>(*this));
	Commands.Add(MakeUnique<CommandQuitRoom>(*this));
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
	if (newIndex <= UserDataPool.Num())
	{
		UserDataPool.Emplace(NewObject<UUserData>());
	}
	UUserData* ptr = UserDataPool[newIndex];
	ptr->Set(name, addr);
	UserDatas.Add(ptr);
}

void FCommandProcessor::PostCompleteChangedOfUserData()
{
	if (ChangedUserList.IsBound()) ChangedUserList.Execute(UserDatas);
}

void FCommandProcessor::PostStartChangedOfRoomData()
{
	RoomDatas.Empty();
}

void FCommandProcessor::AddRoomList(int32 index, const FString& title, int32 current, int32 max)
{
	int32 newIndex = RoomDatas.Num();
	if (newIndex <= RoomDataPool.Num())
	{
		RoomDataPool.Emplace(NewObject<URoomData>());
	}
	URoomData* ptr = RoomDataPool[newIndex];
	ptr->Set(index, title, current, max);
	RoomDatas.Add(ptr);
}

void FCommandProcessor::PostCompleteChangedOfRoomData()
{
	if (ChangedRoomList.IsBound()) ChangedRoomList.Execute(RoomDatas);
}

void FCommandProcessor::PostLoginComplete()
{
	IsLoginState = false;
	SucceededLogin.ExecuteIfBound();
}

void FCommandProcessor::PostLoginFailed(const FString& info)
{
	IsLoginState = true;
	FailedLogin.ExecuteIfBound(info);
}

void FCommandProcessor::PostEnteredRoom()
{
	EnteredRoom.ExecuteIfBound();
}

void FCommandProcessor::PostExitedRoom()
{
	ExitedRoom.ExecuteIfBound();
}

void FCommandProcessor::TurnOnLoginState()
{
	IsLoginState = true;
}

FCommandProcessor::FChangedUserList& FCommandProcessor::GetChangedUserList()
{
	return ChangedUserList;
}

FCommandProcessor::FChangedRoomList& FCommandProcessor::GetChangedRoomList()
{
	return ChangedRoomList;
}

FCommandProcessor::FSucceededLogin& FCommandProcessor::GetSucceededLogin()
{
	return SucceededLogin;
}

FCommandProcessor::FFailedLogin& FCommandProcessor::GetFailedLogin()
{
	return FailedLogin;
}

FCommandProcessor::FEnteredRoom& FCommandProcessor::GetEnteredRoom()
{
	return EnteredRoom;
}

FCommandProcessor::FExitedRoom& FCommandProcessor::GetExitedRoom()
{
	return ExitedRoom;
}

bool FCommandProcessor::ProcessLine(const FString& line)
{
	UE_LOG(LogTemp, Log, TEXT("%s"), *line);

	if(IsLoginState && loginCommand)
	{
		loginCommand->ProcessCommand(line);
		return false;
	}

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


