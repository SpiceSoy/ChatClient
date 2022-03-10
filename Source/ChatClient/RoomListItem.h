// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "RoomListItem.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API URoomListItem : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class URoomListItemInternal* roomListInternalWidget = nullptr;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet(UObject* listItemObject) override;
	virtual void NativeOnItemSelectionChanged(bool isSelected) override;
};
