// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatConnection.h"
#include "Engine/GameInstance.h"
#include "ChatGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class CHATCLIENT_API UChatGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<class UChatTemplate> GetChatWidget() const;
	//TWeakObjectPtr<class UChatConnection> GetChatConnection() const;
	UChatGameInstance();
	~UChatGameInstance();

	void CreateChatWidget(class AChatPlayerController* owner);
	void CreateChatConnection();
protected:
	virtual void Init() override;
private:
	TSubclassOf<class UChatTemplate> ChatTemplateClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChatTemplate* ChatTemplate = nullptr;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//class UChatConnection* ChatConnection = nullptr;
};
