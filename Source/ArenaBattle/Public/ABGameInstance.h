// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "WebConnect.h"
#include "ABGameInstance.generated.h"

class FHouse
{
public:
	TSharedPtr<FHouse> OthersDeed;
	TWeakPtr<FHouse> AccessHouse;
	int32 Size = 10;

	void RequestTokenComplete(const FString& token) {
		UE_LOG(LogClass, Warning, TEXT("Test.."));
	}
};
/**
*
*/
UCLASS()
class ARENABATTLE_API UABGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UABGameInstance();

	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WebService")
		class UWebConnection* WebConnection;

	UPROPERTY()
		class UWebConnection* WebConnectionNew;

	UPROPERTY()
		FStreamableManager AssetLoader;

	UFUNCTION()
		void RequestTokenComplete(const FString& Token);

	UFUNCTION()
		void RequestTokenComplete2(const FString& Token);

};