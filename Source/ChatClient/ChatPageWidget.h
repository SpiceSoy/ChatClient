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
	class UButton* ButtonSend = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UEditableTextBox* TextBoxChat = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class URichTextBlock* TextBoxLog = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UScrollBox* ScrollBoxChat = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextTitle = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UVerticalBox* VerticalBoxCommand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UCommandButton> ClassCommandButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UCommandButton*> CommandButtons;
public:
	FClickedSend& GetClickedSend();
	void AppendLog(const FString& str) const;
	void AppendLog(const FText& text) const;
	void SetChatInput(const FString& str) const;
	void FocusChatInput() const;
	void SetChatRoom(bool isInRoom);
private:
	FClickedSend ClickedSend;

	bool IsInRoom = false;

	const FString& GetCommandPrefix() const;

	UFUNCTION()
	void OnTextCommittedChat(const FText& text, ETextCommit::Type type);

	UFUNCTION(BlueprintCallable)
	void OnClickedSend();

};
