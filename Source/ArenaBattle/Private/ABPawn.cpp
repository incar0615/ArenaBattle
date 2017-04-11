// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaBattle.h"
#include "ABGameInstance.h"
#include "ABPawn.h"


// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	RootComponent = Body;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Body);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Cam"));
	Cam->SetupAttachment(Body);
	Cam->SetRelativeLocationAndRotation(FVector(-200.0f, 0.0, 150.0), FRotator(-20.0f, 0.0f, 0.0f));
	
	Body->SetCapsuleHalfHeight(88.0f);
	Body->SetCapsuleRadius(34.0f);

	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, 270.0f, 0.0f));

	// 해당 CDO를 사용하는 여러 인스턴스에서 해당 변수를 공유해서 사용하기 위해서 static을 쓴다.
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CharM_Cardboard(TEXT("SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard'"));
	Mesh->SetSkeletalMesh(SK_CharM_Cardboard.Object);

	this->AutoPossessPlayer = EAutoReceiveInput::Player0;

	MaxHP = 100.0f;

	
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;

	int32 NewIndex = FMath::RandRange(0, CharacterAssets.Num() - 1);
	UABGameInstance* ABGameInstance = Cast<UABGameInstance>(GetGameInstance());

	for (int i = 0; i < CharacterAssets.Num() - 1; i++) {
		ABGameInstance->AssetLoader.SimpleAsyncLoad(CharacterAssets[i]);
	}

	if (ABGameInstance)
	{
		TAssetPtr<USkeletalMesh> NewCharacter = Cast<USkeletalMesh>(ABGameInstance->AssetLoader.SynchronousLoad(CharacterAssets[NewIndex]));
		if (NewCharacter)
		{
			Mesh->SetSkeletalMesh(NewCharacter.Get());
		}
	}
}

// Called every frame
void AABPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

