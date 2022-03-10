//=================================================================================================
// @file UserListEntry.h
//
// @brief 이용자 목록 리스트뷰에 사용될 엔트리 UI 클래스입니다.
//
// @date 2022/03/08
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UserListEntry.generated.h"


/**
 *
 */
UCLASS()
class CHATCLIENT_API UUserNameListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

private:
	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
		class UTextBlock* TextBlockUserName = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UButton* ButtonView = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UButton* ButtonWhisper = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UButton* ButtonInvite = nullptr;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta = ( AllowPrivateAccess = "true" ) )
	class UUserData* UserData = nullptr;
protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnListItemObjectSet( UObject* ListItemObject ) override;
	virtual void NativeOnItemSelectionChanged( bool isSelected ) override;
private:
	UFUNCTION()
		void OnClickedButtonView();
	UFUNCTION()
	void OnClickedButtonWhisper();
	UFUNCTION()
	void OnClickedButtonInvite();
};
