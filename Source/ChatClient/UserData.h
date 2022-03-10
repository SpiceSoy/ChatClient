// Fill out your copyright notice in the Description page of Project Settings.

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

public:
	UUserData();
	virtual ~UUserData() = default;
	void Set(const FString& name, const FString address);
	void SetPtr(const TWeakObjectPtr<class UChatConnection>& connection, const TWeakObjectPtr<class UChatTemplate>& chatUi);
	const FString& GetName() const;
	const FString& GetAddress() const;
	const TWeakObjectPtr<class UChatConnection>& GetConnection() const;
	const TWeakObjectPtr<class UChatTemplate>& GetChatUi() const;
private:
	FString Name;
	FString Address;
	TWeakObjectPtr<UChatConnection> Connection;
	TWeakObjectPtr<UChatTemplate> ChatUi;

};
