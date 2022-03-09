// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatTemplate.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UChatTemplate : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonTabConnect;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonTabChat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidgetSwitcher* WidgetSwitcher;
public:
	UFUNCTION()
	void OnClickedTabConnect();
	UFUNCTION()
	void OnClickedTabChat();
};
