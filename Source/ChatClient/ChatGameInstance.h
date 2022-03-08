// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatConnection.h"
#include "Engine/GameInstance.h"
#include "ChatGameInstance.generated.h"



class UChatWidget;

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UChatGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<UChatWidget> GetChatWidget() const;
	TWeakObjectPtr<class UChatConnection> GetChatConnection() const;
	UChatGameInstance();
	~UChatGameInstance();

	void CreateChatWidget(class AChatPlayerController* owner);
	void CreateChatConnection();
protected:
	virtual void Init() override;
private:
	TSubclassOf<class UChatWidget> ChatWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChatWidget* ChatWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChatConnection* ChatConnection = nullptr;
};
