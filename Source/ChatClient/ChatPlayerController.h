//=================================================================================================
// @file ChatPlayerController.h
//
// @brief 커넥션 생성 및 위젯 생성, 커넥션의 틱 함수를 부르기 위한 플레이어 컨트롤러 클래스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "ChatConnection.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChatPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class CHATCLIENT_API AChatPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	TWeakObjectPtr<class UChatTemplate> ChatTemplate = nullptr;
	TWeakObjectPtr<class UChatConnection> ChatConnection = nullptr;

public:
	AChatPlayerController();
	~AChatPlayerController();

	virtual void BeginPlay() override;
	virtual void PlayerTick(float deltaTime) override;
};
