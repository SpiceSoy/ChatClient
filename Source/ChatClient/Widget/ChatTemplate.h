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
	DECLARE_DELEGATE(FChangedTab);
protected:
	virtual void NativeOnInitialized() override;
private:
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
	class UConnectWidget* ConnectWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UChatPageWidget* LobbyWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UUserListWidget* UserListWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class URoomListWidget* RoomListWidget = nullptr;

	FChangedTab ChagedTabConnect;
	FChangedTab ChagedTabLobby;
	FChangedTab ChagedTabUserList;
	FChangedTab ChagedTabRoomList;

public:
	UFUNCTION()
	void OnClickedTabConnect();
	UFUNCTION()
	void OnClickedTabLobby();
	UFUNCTION()
	void OnClickedTabUserList();
	UFUNCTION()
	void OnClickedTabRoomList();

	void SetWidgetIndex(int32 index) const;
	void SetTitle(const FString& title) const;
	void SetUserName(const FString& title) const;

	TWeakObjectPtr<UConnectWidget> GetConnectWidget() const;
	TWeakObjectPtr<UChatPageWidget> GetLobbyWidget() const;
	TWeakObjectPtr<UUserListWidget> GetUserListWidget() const;
	TWeakObjectPtr<URoomListWidget> GetRoomListWidget() const;

	FChangedTab& GetChagedTabConnect();
	FChangedTab& GetChagedTabLobby();
	FChangedTab& GetChagedTabUserList();
	FChangedTab& GetChagedTabRoomList();

};
