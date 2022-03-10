// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserListWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UUserListWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UListView* ListViewUser;
public:
	void SetUserList(const TArray<class UUserData*>& arr) const;
};
