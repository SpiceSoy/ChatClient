// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChatConnection.h"
#include "ChatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API AChatPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	AChatPlayerController();
	~AChatPlayerController();
	virtual void BeginPlay() override;
	virtual void PlayerTick(float deltaTime) override;
private:
	TWeakObjectPtr<class UChatWidget> ChatWidget = nullptr;
	TWeakObjectPtr<class UChatConnection> ChatConnection = nullptr;
};
