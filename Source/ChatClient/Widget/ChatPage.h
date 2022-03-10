//=================================================================================================
// @file ChatPage.h
//
// @brief 채팅 페이지 UI를 위한 위젯 클래스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatPage.generated.h"


/**
 *
 */
UCLASS()
class CHATCLIENT_API UChatPage : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DELEGATE_OneParam( FClickedSend, const FString& );
private:
	FClickedSend ClickedSend;
	bool IsInRoom = false;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UButton* ButtonSend = nullptr;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UEditableTextBox* TextBoxChat = nullptr;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class URichTextBlock* TextBoxLog = nullptr;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UScrollBox* ScrollBoxChat = nullptr;
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UTextBlock* TextTitle = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UVerticalBox* VerticalBoxCommand;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	TSubclassOf<class UCommandButton> ClassCommandButton;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	TArray<UCommandButton*> CommandButtons;
public:
	FClickedSend& GetClickedSend();
	void AppendLog( const FString& str ) const;
	void AppendLog( const FText& text ) const;
	void SetChatInput( const FString& str ) const;
	void FocusChatInput() const;
	void SetChatRoom( bool isInRoom );
protected:
	virtual void NativeOnInitialized() override;
private:
	const FString& GetCommandPrefix() const;
private:
	UFUNCTION()
	void OnTextCommittedChat( const FText& text, ETextCommit::Type type );

	UFUNCTION( BlueprintCallable )
	void OnClickedSend();

};
