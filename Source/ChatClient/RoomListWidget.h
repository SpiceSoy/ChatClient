// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomListWidget.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API URoomListWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UListView* ListViewRoom;
public:
	void SetRoomList(const TArray<class URoomData*>& arr);
};
