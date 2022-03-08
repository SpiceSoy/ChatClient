// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "../UserData.h"


/**
 * 
 */
class CHATCLIENT_API FCommandProcessor
{
	DECLARE_DELEGATE_OneParam(FChangedUserList, const TArray<UUserData*>&);
public:
	FCommandProcessor();
	FCommandProcessor(const FCommandProcessor&) = delete;
	~FCommandProcessor();

	FCommandProcessor& operator=(const FCommandProcessor&) = delete;

	FChangedUserList& GetChangedUserList();
private:
	FChangedUserList ChangedUserList;
	TArray<UUserData*> UserDataPool;
	TArray<UUserData*> UserDatas;
	//TUniquePtr<BaseCommand> Commandssss;
	TArray<TUniquePtr<BaseCommand>> Commands;
	TArray<int32> CommandBypassCount;
	static constexpr int32 NO_COMMAND = -1;
	int32 CurrentCommand = NO_COMMAND;
public:
	void PostStartChangedOfUserData();
	void AddUserList(const FString& name, const FString& addr);
	void PostCompleteChangedOfUserData();
	bool ProcessLine(const FString& line);
};
