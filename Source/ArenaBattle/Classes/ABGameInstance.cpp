// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"

// �������� ���� ��ü (������ ������ ���)
UABGameInstance::UABGameInstance() {
	AB_LOG(Warning, TEXT("Constructor Call Start"));
	WebConnect = CreateDefaultSubobject<UWebConnect>(TEXT("MyWebConnection"));
	AB_LOG(Warning, TEXT("Constructor Call End"));
}


// �����÷��̻󿡼� ����
void UABGameInstance::Init() {

	Super::Init();
	AB_LOG_CALLONLY(Warning);

	TArray<UObject *> DefaultSubobjects;
	GetDefaultSubobjects(DefaultSubobjects);
	for (const auto& Entry : DefaultSubobjects)
	{
		AB_LOG(Warning, TEXT("DefaultSubobject : %s"), *Entry->GetClass()->GetName());
		AB_LOG(Warning, TEXT("Outer of DefaultSubobject : %s"), *Entry->GetOuter()->GetClass()->GetName());
	}

	WebConnectionNew = NewObject<UWebConnect>(this);
	AB_LOG(Warning, TEXT("Outer of NewObject : %s"), *WebConnectionNew->GetOuter()->GetClass()->GetName());

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
�����ڸ����� �� �� ������ �Ÿ� üũ
�Ÿ��� ���� �����ڸ� ����Ʈ�� ���� �� ����
*/