// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ABAnimNotifyState_AttackDash.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABAnimNotifyState_AttackDash : public UAnimNotifyState
{
	GENERATED_BODY()


public :
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ASD")
	float DashPower;

	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime);
	
};
