// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

// 공용으로 쓰는 객체 (일종의 프리팹 비슷)
UABGameInstance::UABGameInstance() {
	AB_LOG(Warning, TEXT("Constructor Call Start"));
	WebConnect = CreateDefaultSubobject<UWebConnect>(TEXT("MyWebConnection"));
	AB_LOG(Warning, TEXT("Constructor Call End"));
}


// 게임플레이상에서 실행
void UABGameInstance::Init() {
	
	AB_LOG_CALLONLY(Warning);
	Super::Init();

	WebConnect2 = NewObject<UWebConnect>(this);

	WebConnect2->GetOuter();
	UClass* ClassInfo1 = WebConnect->GetClass();
	UClass* ClassInfo2 = UWebConnect::StaticClass(); 

	if (ClassInfo1 == ClassInfo2)
	{
		AB_LOG(Warning, TEXT("ClassInfo1 is same with ClassInfo2"));
	}

	for (TFieldIterator<UProperty> It(ClassInfo1); It; ++It)
	{
		AB_LOG(Warning, TEXT("Field : %s, Type : %s"), *It->GetName(), *It->GetClass()->GetName());

		UStrProperty* StrProp = FindField<UStrProperty>(ClassInfo1, *It->GetName());

		if (StrProp)
		{
			AB_LOG(Warning, TEXT("Value = %s"), *StrProp->GetPropertyValue_InContainer(WebConnect));
		}
	}

	for (const auto& Entry : ClassInfo1->NativeFunctionLookupTable)
	{
		AB_LOG(Warning, TEXT("Function = %s"), *Entry.Name.ToString());
		//UFunction* Func1 = ClassInfo1->FindFunctionByName(Entry.Name);
		UFunction* Func1 = ClassInfo1->FindFunctionByName(FName("RequestToken"));
		if (Func1->ParmsSize == 0)
		{
			WebConnect->ProcessEvent(Func1, NULL);
		}
	}

	TArray<UObject *> DefaultSubobjects;
	GetDefaultSubobjects(DefaultSubobjects);
	for (const auto& Entry : DefaultSubobjects)
	{
		AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetName());
		AB_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *Entry->GetOuter()->GetClass()->GetFullName());
	}

	UWorld* CurrentWorld = GetWorld();
    for (const auto& Entry : FActorRange(CurrentWorld))
    {
        AB_LOG(Warning, TEXT("Actor : %s"), *Entry->GetName());
        TArray<UObject* > Components;
        Entry->GetDefaultSubobjects(Components);
        for (const auto& CEntry : Components)
        {
            AB_LOG(Warning, TEXT(" -- Component : %s"), *CEntry->GetName());
        }
    }

	for (TActorIterator<AStaticMeshActor> It(CurrentWorld); It; ++It)
	{
		AB_LOG(Warning, TEXT("StaticMesh Actor : %s"), *It->GetName());
	}

	WebConnect->Host = TEXT("localhost");
	WebConnectionNew->Host = TEXT("127.0.0.1");

	for (TObjectIterator<UWebConnect> It; It; ++It)
	{
		UWebConnect* Conn = *It;
		AB_LOG(Warning, TEXT("WebConnection Object Host : %s"), *Conn->Host);
	}
}

/*
가장자리에서 각 점 까지의 거리 체크
거리가 같은 가장자리 포인트와 점의 을 저장
*/