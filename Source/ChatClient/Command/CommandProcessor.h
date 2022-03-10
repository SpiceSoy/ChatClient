// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCommand.h"
#include "../UserData.h"
#include "../RoomData.h"


/**
 * 
 */
class CHATCLIENT_API FCommandProcessor
{
	DECLARE_DELEGATE_OneParam(FChangedUserList, const TArray<UUserData*>&);
	DECLARE_DELEGATE_OneParam(FChangedRoomList, const TArray<URoomData*>&);
	DECLARE_DELEGATE(FSucceededLogin);
	DECLARE_DELEGATE_OneParam(FFailedLogin, const FString&);
	DECLARE_DELEGATE(FEnteredRoom);
	DECLARE_DELEGATE(FExitedRoom);
public:
	FCommandProcessor();
	FCommandProcessor(const FCommandProcessor&) = delete;
	~FCommandProcessor();

	FCommandProcessor& operator=(const FCommandProcessor&) = delete;

	FChangedUserList& GetChangedUserList();
	FChangedRoomList& GetChangedRoomList();
	FSucceededLogin& GetSucceededLogin();
	FFailedLogin& GetFailedLogin();
	FEnteredRoom& GetEnteredRoom();
	FExitedRoom& GetExitedRoom();
private:
	FChangedUserList ChangedUserList;
	FChangedRoomList ChangedRoomList;
	FSucceededLogin SucceededLogin;
	FFailedLogin FailedLogin;
	FEnteredRoom EnteredRoom;
	FExitedRoom ExitedRoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UUserData*> UserDataPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UUserData*> UserDatas;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<URoomData*> RoomDataPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<URoomData*> RoomDatas;

	TUniquePtr<BaseCommand> loginCommand;
	TArray<TUniquePtr<BaseCommand>> Commands;
	TArray<int32> CommandBypassCount;

	static constexpr int32 NO_COMMAND = -1;
	int32 CurrentCommand = NO_COMMAND;

	bool IsLoginState = true;
public:
	bool ProcessLine(const FString& line);

	void PostStartChangedOfUserData();
	void AddUserList(const FString& name, const FString& addr);
	void PostCompleteChangedOfUserData();

	void PostStartChangedOfRoomData();
	void AddRoomList(int32 index, const FString& title, int32 current, int32 max);
	void PostCompleteChangedOfRoomData();

	void PostLoginComplete();
	void PostLoginFailed(const FString& info);

	void PostEnteredRoom();
	void PostExitedRoom();

	void TurnOnLoginState();
};
