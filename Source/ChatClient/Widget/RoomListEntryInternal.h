//=================================================================================================
// @file RoomListEntryInternal.h
//
// @brief RoomListEntry가 실시간 반영이 불가능해서 실시간 갱신을 위해 만든 내부 위젯입니다.
//
// @date 2022/03/10
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomListEntryInternal.generated.h"


/**
 * 
 */
UCLASS()
class CHATCLIENT_API URoomListEntryInternal : public UUserWidget
{
	GENERATED_BODY()


private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextName = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextIndex = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextUser = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonView = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonEnter = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class URoomData* RoomData = nullptr;
public:
	void Set(URoomData* roomData);

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeTick(const FGeometry& myGeometry, float inDeltaTime) override;
private:
	UFUNCTION()
	void OnClickedViewButton();
	UFUNCTION()
	void OnClickedEnterButton();
	UFUNCTION()
	void OnDataChanged();
};
