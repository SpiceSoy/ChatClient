//=================================================================================================
// @file ChatGameInstance.h
//
// @brief 채팅 위젯, 채팅 커넥션 클래스 인스턴스를 보유하기 위한 게임 인스턴스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "ChatConnection.h"
#include "CoreMinimal.h"
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
	TWeakObjectPtr<class UChatMainWidget> GetChatWidget() const;
	TWeakObjectPtr<class UChatConnection> GetChatConnection() const;
	UChatGameInstance();
	~UChatGameInstance();

	void CreateChatWidget( class AChatPlayerController* owner );
	void CreateChatConnection();
protected:
	virtual void Init() override;
private:
	TSubclassOf<class UChatMainWidget> ChatTemplateClass;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UChatMainWidget* ChatTemplate = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UChatConnection* ChatConnection = nullptr;
};
