// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	UChatGameInstance();
	~UChatGameInstance();

	void CreateChatWidget(class AChatPlayerController* owner);
protected:
	virtual void Init() override;
private:
	TSubclassOf<class UChatWidget> ChatWidgetClass;
	class UChatWidget* ChatWidget = nullptr;
};
