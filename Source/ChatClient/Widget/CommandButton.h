//=================================================================================================
// @file CommandButton.h
//
// @brief 명령어 버튼을 위한 람다 함수 등록 버튼 클래스 입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include <functional>
#include "CommandButton.generated.h"


/**
 *
 */
UCLASS()
class CHATCLIENT_API UCommandButton : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
		class UButton* Button;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UTextBlock* Title;

	std::function<void()> Functor;

public:
	void SetFuctor( const std::function<void()>& functor );
	void SetTitle( const FString& title );
	void Set( const FString& title, const std::function<void()>& functor );

protected:
	virtual void NativeOnInitialized() override;
private:
	UFUNCTION()
	void CallFuntor();
};
