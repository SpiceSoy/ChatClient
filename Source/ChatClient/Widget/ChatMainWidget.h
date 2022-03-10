//=================================================================================================
// @file ChatMainWidget.h
//
// @brief 위젯 메인 페이지 클래스입니다.
//
// @date 2022/03/07
//
// Copyright 2022 Netmarble Neo, Inc. All Rights Reserved.
//=================================================================================================


#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatMainWidget.generated.h"


/**
 * 
 */
UCLASS()
class CHATCLIENT_API UChatMainWidget : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DELEGATE(FChangedTab);
private:
	FChangedTab ChagedTabConnect;
	FChangedTab ChagedTabLobby;
	FChangedTab ChagedTabRoomList;
	FChangedTab ChagedTabUserList;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextTitle;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* TextName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonTabConnect = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonTabLobby = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonTabUserList = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* ButtonTabRoomList = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UWidgetSwitcher* WidgetSwitcher = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UConnectPage* ConnectWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChatPage* ChatPage = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UUserListPage* UserListWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class URoomListPage* RoomListWidget = nullptr;
public:
	void SetWidgetIndex(int32 index) const;
	void SetTitle(const FString& title) const;
	void SetUserName(const FString& title) const;

	TWeakObjectPtr<UChatPage> GetChatPage() const;
	TWeakObjectPtr<UConnectPage> GetConnectPage() const;
	TWeakObjectPtr<URoomListPage> GetRoomListPage() const;
	TWeakObjectPtr<UUserListPage> GetUserListPage() const;

	FChangedTab& GetChagedTabConnect();
	FChangedTab& GetChagedTabChat();
	FChangedTab& GetChagedTabRoomList();
	FChangedTab& GetChagedTabUserList();

	UFUNCTION()
	void OnClickedTabConnect();
	UFUNCTION()
	void OnClickedTabChat();
	UFUNCTION()
	void OnClickedTabUserList();
	UFUNCTION()
	void OnClickedTabRoomList();
protected:
	virtual void NativeOnInitialized() override;
};
