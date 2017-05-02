// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	AB_LOG(Warning, TEXT("Constructor Call Start"));
	WebConnection = CreateDefaultSubobject<UWebConnection>(TEXT("MyWebConnection"));
	AB_LOG(Warning, TEXT("Constructor Call End"));
}

void UABGameInstance::RequestTokenComplete(const FString& Token)
{
	AB_LOG(Warning, TEXT("Token : %s"), *Token);
}
void UABGameInstance::RequestTokenComplete2(const FString& Token)
{
	AB_LOG(Warning, TEXT("Token2 : %s"), *Token);
}

void UABGameInstance::Init()
{
	Super::Init();
	AB_LOG_CALLONLY(Warning);

	FHouse * HouseNew = new FHouse();

	//WebConnection->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete);
	//WebConnection->TokenCompleteDelegate.AddUObject(this, &UABGameInstance::RequestTokenComplete2);
	//WebConnection->TokenCompleteDelegate.AddRaw(HouseNew, &FHouse::RequestTokenComplete);
	
	WebConnection->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete);
	WebConnection->TokenCompleteDelegate.AddDynamic(this, &UABGameInstance::RequestTokenComplete2);

	WebConnection->RequestToken(TEXT("destiny"));


	FString PackageName = TEXT("/Temp/SavedWebConnection");
	UPackage* NewPackage = CreatePackage(nullptr, *PackageName);
	WebConnectionNew = NewObject<UWebConnection>(NewPackage);
	FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension());

	WebConnectionNew->Host = TEXT("127.0.0.7");
	WebConnectionNew->URI = TEXT("/");
	if (UPackage::SavePackage(NewPackage, WebConnectionNew, RF_Standalone, *PackageFileName))
	{
		UPackage* SavedPackage = ::LoadPackage(NULL, *PackageFileName, LOAD_None);
		TArray<UObject *> ObjectsInPackage;
		GetObjectsWithOuter(SavedPackage, ObjectsInPackage, false);
		for (const auto& EachObject : ObjectsInPackage)
		{
			UWebConnection* WebConnectionFromFile = Cast<UWebConnection>(EachObject);
			if (WebConnectionFromFile)
			{
				AB_LOG(Warning, TEXT("WebConnection From File : Host %s , URI %s"), *WebConnectionFromFile->Host, *WebConnectionFromFile->URI);
			}
		}
	}
}