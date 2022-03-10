// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomData.h"

URoomData::URoomData()
	: UObject()
{
	Set(93939393, TEXT("ERROR_ROOM"), 0, 0);
}

void URoomData::Set(int32 index, const FString& title, int32 currnet, int32 max)
{
	Index = index;
	Title = title;
	CurrentUserCount = currnet;
	MaxUserCount = max;
}

const FString& URoomData::GetTitle() const
{
	return Title;
}

int32 URoomData::GetIndex() const
{
	return Index;
}

int32 URoomData::GetCurrentUserCount() const
{
	return CurrentUserCount;
}	

int32 URoomData::GetMaxUserCount() const
{
	return MaxUserCount;
}
