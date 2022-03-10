// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <functional>
#include "CommandButton.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UCommandButton : public UUserWidget
{
	GENERATED_BODY()
	

public:
	void SetFuctor(const std::function<void()>& functor);
	void SetTitle(const FString& title);
	void Set(const FString& title, const std::function<void()>& functor);
protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* Title;

	std::function<void()> Functor;

	UFUNCTION()
	void CallFuntor();
};
