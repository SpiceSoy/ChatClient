// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomListItemInternal.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API URoomListItemInternal : public UUserWidget
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
