// Fill out your copyright notice in the Description page of Project Settings.

#include "WebService.h"
#include "WebConnect.h"

DEFINE_LOG_CATEGORY(WebConnection);

UWebConnection::UWebConnection()
{
	UE_LOG(WebConnection, Warning, TEXT("WebConnection Constructor Call!"));
	Host = TEXT("localhost:8000");
	URI = TEXT("/");
}

void UWebConnection::RequestToken(const FString& UserID)
{
	UE_LOG(WebConnection, Warning, TEXT("Request Token Call!"));
	//TokenCompleteDelegate.ExecuteIfBound(TEXT("0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));
	TokenCompleteDelegate.Broadcast(TEXT("0LCJydGkiOiI2a3NjVE9pTUNESVZWM05qVTIyUnlTIn0.VJyMOicM"));
}