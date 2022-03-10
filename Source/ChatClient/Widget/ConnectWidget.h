// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConnectWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UConnectWidget : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DELEGATE_TwoParams(FClickedConnectBtn, uint32, uint32);
	DECLARE_DELEGATE_OneParam(FClickedLoginBtn, const FString&);
protected:
	virtual void NativeOnInitialized() override;

	bool IsConnected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEditableTextBox* TextBoxIp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEditableTextBox* TextBoxPort;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEditableTextBox* TextBoxName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonConnect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonLogin;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextBlockConnect;
	FClickedConnectBtn ClickedConnectBtn;
	FClickedLoginBtn ClickedLoginBtn;
public:
	FClickedConnectBtn& GetClickedConnectBtn();
	FClickedLoginBtn& GetClickedLoginBtn();

	void SetConnectionInfoText(const FString& text);
protected:
	UFUNCTION(BlueprintCallable)
	void OnClickedConnectBtn();

	UFUNCTION(BlueprintCallable)
	void OnClickedChatLoginBtn();

	UFUNCTION(BlueprintCallable)
	void OnChangedIpText(const FText& text);

	UFUNCTION(BlueprintCallable)
	void OnChangedPortText(const FText& text);
};
