// Fill out your copyright notice in the Description page of Project Settings.


#include "UserData.h"
#include "ChatTemplate.h"
#include "ChatConnection.h"

UUserData::UUserData()
	: UObject()
{
	Set(TEXT("ERROR_NAME"), TEXT("ERR.ERR.ERR.ERR"));
}

void UUserData::Set(const FString& name, const FString address)
{
	Name = name;
	Address = address;
}

void UUserData::SetPtr(const TWeakObjectPtr<UChatConnection>& connection, const TWeakObjectPtr<UChatTemplate>& chatUi)
{
	Connection = connection;
	ChatUi = chatUi;
}

const FString& UUserData::GetName() const
{
	return Name;
}

const FString& UUserData::GetAddress() const
{
	return Address;
}

const TWeakObjectPtr<UChatConnection>& UUserData::GetConnection() const
{
	return Connection;
}

const TWeakObjectPtr<UChatTemplate>& UUserData::GetChatUi() const
{
	return ChatUi;
}
