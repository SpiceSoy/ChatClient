// Fill out your copyright notice in the Description page of Project Settings.


#include "UserData.h"

UUserData::UUserData()
{
	Set(TEXT("ERROR_NAME"), TEXT("ERR.ERR.ERR.ERR"));
}

void UUserData::Set(const FString& name, const FString address)
{
	Name = name;
	Address = address;
}

const FString& UUserData::GetName() const
{
	return Name;
}

const FString& UUserData::GetAddress() const
{
	return Address;
}
