//=================================================================================================
// @file ConnectPage.h
//
// @brief 서버와 연결하기 위한 UI 페이지 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConnectPage.generated.h"


/**
 *
 */
UCLASS()
class CHATCLIENT_API UConnectPage : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DELEGATE_TwoParams( FClickedConnectBtn, uint32, uint32 );
	DECLARE_DELEGATE_OneParam( FClickedLoginBtn, const FString& );
private:
	bool IsConnected = false;
	FClickedConnectBtn ClickedConnectBtn;
	FClickedLoginBtn ClickedLoginBtn;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UEditableTextBox* TextBoxIp;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UEditableTextBox* TextBoxPort;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UEditableTextBox* TextBoxName;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UButton* ButtonConnect;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UButton* ButtonLogin;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UTextBlock* TextBlockConnect;
public:
	FClickedConnectBtn& GetClickedConnectBtn();
	FClickedLoginBtn& GetClickedLoginBtn();

	void SetConnectionInfoText( const FString& text );
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION( BlueprintCallable )
	void OnClickedConnectBtn();

	UFUNCTION( BlueprintCallable )
	void OnClickedChatLoginBtn();

	UFUNCTION( BlueprintCallable )
	void OnChangedIpText( const FText& text );

	UFUNCTION( BlueprintCallable )
	void OnChangedPortText( const FText& text );


};
