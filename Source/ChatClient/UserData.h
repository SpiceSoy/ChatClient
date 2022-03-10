//=================================================================================================
// @file UserData.h
//
// @brief 이용자 목록 공유를 위한 대화방 정보 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserData.generated.h"


/**
 * 
 */
UCLASS()
class CHATCLIENT_API UUserData : public UObject
{
	GENERATED_BODY()

private:
	FString Name;
	FString Address;
	TWeakObjectPtr<UChatConnection> Connection;
	TWeakObjectPtr<UChatTemplate> ChatUi;
	constexpr static FString ERROR_ADDR = TEXT("ERR.ERR.ERR.ERR");
	constexpr static FString ERROR_NAME = TEXT("ERROR_NAME");
public:
	UUserData();
	virtual ~UUserData() = default;

	void Set(const FString& name, const FString address);
	void SetPtr(const TWeakObjectPtr<class UChatConnection>& connection, const TWeakObjectPtr<class UChatTemplate>& chatUi);
	const FString& GetName() const;
	const FString& GetAddress() const;
	const TWeakObjectPtr<class UChatConnection>& GetConnection() const;
	const TWeakObjectPtr<class UChatTemplate>& GetChatUi() const;

};
