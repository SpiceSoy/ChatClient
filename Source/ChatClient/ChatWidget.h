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

	DECLARE_DELEGATE_TwoParams(FConnectBtnPressed, uint32, uint32);
	DECLARE_DELEGATE_OneParam(FChatSendBtnPressed, const FString&);
public:
	FConnectBtnPressed& GetConnectBtnPressed();
	FChatSendBtnPressed& GetChatSendBtnPressed();
	void AppendLog(const FString& str) const;
	void AppendLog(const FText& text) const;
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEditableTextBox* TextBoxIp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEditableTextBox* TextBoxPort;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMultiLineEditableTextBox* TextBoxLog;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ConnectButton;

	FConnectBtnPressed ConnectBtnPressed;
	FChatSendBtnPressed ChatSendBtnPressed;

	UFUNCTION(BlueprintCallable)
	void OnTextChangedIpAddress(const FText& text);

	UFUNCTION(BlueprintCallable)
	void OnTextChangedIpPort(const FText& text);

	UFUNCTION(BlueprintCallable)
	void OnConnectBtnPressed();

	UFUNCTION(BlueprintCallable)
	void OnChatSendBtnPressed();
};
