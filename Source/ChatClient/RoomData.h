// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RoomData.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API URoomData : public UObject
{
	GENERATED_BODY()
	DECLARE_DELEGATE(FChangedData);
public:
	URoomData();
	virtual ~URoomData() = default;
	void Set(int32 index, const FString& title, int32 currentUserCount, int32 maxUserCount);
	void SetPtr(const TWeakObjectPtr<class UChatConnection>& connection, const TWeakObjectPtr<class UChatTemplate>& chatUi);
	const FString& GetTitle() const;
	int32 GetIndex() const;
	int32 GetCurrentUserCount() const;
	int32 GetMaxUserCount() const;
	const TWeakObjectPtr<UChatConnection>& GetConnection() const;
	const TWeakObjectPtr<UChatTemplate>& GetChatUi() const;

	FChangedData& GetChangedData();
private:
	int32 Index;
	FString Title;
	int32 CurrentUserCount;
	int32 MaxUserCount;
	TWeakObjectPtr<UChatConnection> Connection;
	TWeakObjectPtr<UChatTemplate> ChatUi;
	FChangedData ChangedData;
};
