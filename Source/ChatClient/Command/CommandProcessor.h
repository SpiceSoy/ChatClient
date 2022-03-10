//=================================================================================================
// @file CommandProcessor.h
//
// @brief 커맨드 모음 및 커맨드 처리, 이벤트 통지를 위한 모음 클래스 입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Command/BaseCommand.h"
#include "RoomData.h"
#include "UserData.h"
#include "CoreMinimal.h"


/**
 *
 */
class CHATCLIENT_API FCommandProcessor
{
	DECLARE_DELEGATE_OneParam( FChangedUserList, const TArray<UUserData*>& );
	DECLARE_DELEGATE_OneParam( FChangedRoomList, const TArray<URoomData*>& );
	DECLARE_DELEGATE( FSucceededLogin );
	DECLARE_DELEGATE_OneParam( FFailedLogin, const FString& );
	DECLARE_DELEGATE( FEnteredRoom );
	DECLARE_DELEGATE( FExitedRoom );
private:
	FChangedUserList ChangedUserList;
	FChangedRoomList ChangedRoomList;
	FSucceededLogin SucceededLogin;
	FFailedLogin FailedLogin;
	FEnteredRoom EnteredRoom;
	FExitedRoom ExitedRoom;

	TUniquePtr<BaseCommand> loginCommand;
	TArray<TUniquePtr<BaseCommand>> Commands;
	TArray<int32> CommandBypassCounts;

	static constexpr int32 NO_COMMAND = -1;
	int32 CurrentCommand = NO_COMMAND;
	bool IsLoginState = true;

private:
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	TArray<UUserData*> UserDataPool;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	TArray<UUserData*> UserDatas;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	TArray<URoomData*> RoomDataPool;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	TArray<URoomData*> RoomDatas;
public:
	FCommandProcessor();
	FCommandProcessor( const FCommandProcessor& ) = delete;
	~FCommandProcessor();

	FCommandProcessor& operator=( const FCommandProcessor& ) = delete;

	FChangedUserList& GetChangedUserList();
	FChangedRoomList& GetChangedRoomList();
	FSucceededLogin& GetSucceededLogin();
	FFailedLogin& GetFailedLogin();
	FEnteredRoom& GetEnteredRoom();
	FExitedRoom& GetExitedRoom();

	bool ProcessLine( const FString& line );

	void PostStartChangedOfUserData();
	void AddUserList( const FString& name, const FString& addr );
	void PostCompleteChangedOfUserData();

	void PostStartChangedOfRoomData();
	void AddRoomList( int32 index, const FString& title, int32 current, int32 max );
	void PostCompleteChangedOfRoomData();

	void PostLoginComplete();
	void PostLoginFailed( const FString& info );

	void PostEnteredRoom();
	void PostExitedRoom();

	void TurnOnLoginState();
};
