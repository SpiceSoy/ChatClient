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

public:
	URoomData();
	virtual ~URoomData() = default;
	void Set(int32 index, const FString& title, int32 currentUserCount, int32 maxUserCount);
	const FString& GetTitle() const;
	int32 GetIndex() const;
	int32 GetCurrentUserCount() const;
	int32 GetMaxUserCount() const;

private:
	int32 Index;
	FString Title;
	int32 CurrentUserCount;
	int32 MaxUserCount;
};
