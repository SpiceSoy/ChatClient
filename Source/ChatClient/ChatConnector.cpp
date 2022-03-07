// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatConnector.h"
#include "ChatWidget.h"
#include "ChatGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AChatConnector::AChatConnector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChatConnector::BeginPlay()
{
	Super::BeginPlay();
	//TWeakObjectPtr<UChatWidget> a = Cast<UChatGameInstance>(GetGameInstance())->GetChatWidget();
	//if (a.IsValid())
	//{
	//	UE_LOG(LogTemp, Log, TEXT("CALL AChatConnector::BeginPlay"));
	//	a->AddToViewport();
	//	UE_LOG(LogTemp, Log, TEXT("CALL AChatConnector::AddToViewport %d"), a.Get());
	//}
		
}

// Called every frame
void AChatConnector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

