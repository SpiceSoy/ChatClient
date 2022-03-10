// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatPageWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UChatPageWidget : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DELEGATE_OneParam(FClickedSend, const FString&);
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonSend;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEditableTextBox* TextBoxChat;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class URichTextBlock* TextBoxLog;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UScrollBox* ScrollBoxChat;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextTitle;
public:
	FClickedSend& GetClickedSend();
	void AppendLog(const FString& str) const;
	void AppendLog(const FText& text) const;
private:
	FClickedSend ClickedSend;

	UFUNCTION()
	void OnTextCommittedChat(const FText& text, ETextCommit::Type type);

	UFUNCTION(BlueprintCallable)
	void OnClickedSend();

};
