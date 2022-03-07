//=================================================================================================
// @file UChatWidget.h
//
// @brief Custom widget for chatting client
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatWidget.generated.h"

/**
 *
 */
UCLASS()
class CHATCLIENT_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEditableTextBox* TextBoxIp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UEditableTextBox* TextBoxPort;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
		void OnTextChangedIpAddress(const FText& text);

	UFUNCTION()
		void OnTextChangedIpPort(const FText& text);
};
