// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_RabbitBase.h"

#include "Components/C_AC_SensorBase.h"

#include <Components/SkeletalMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/ArrowComponent.h>
#include <Animation/AnimBlueprint.h>

// Sets default values
AC_RabbitBase::AC_RabbitBase()
{
	PrimaryActorTick.bCanEverTick = false;

	//SkeletalMeshComponentの初期化
	static auto MeshAsset = LoadObject<USkeletalMesh>(NULL, TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/SK_Rabbit.SK_Rabbit'"));
	if (MeshAsset)
	{
		auto* mesh = GetMesh();
		mesh->SetSkeletalMeshAsset(Cast<USkeletalMesh>(MeshAsset));
		mesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -44.f), FRotator(0.f, -90.f, 0.f));

		//アニメーションの設定
		mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		static auto ABPAsset = LoadClass<UAnimInstance>(NULL, TEXT("/Script/Engine.AnimBlueprint'/Game/Animations/ABP_Rabbit.ABP_Rabbit_c'"));
		if (ABPAsset)
		{
			mesh->AnimClass = ABPAsset;
		}
	}

	//CapsuleComponentの初期化
	GetCapsuleComponent()->SetCapsuleHalfHeight(44.f);
}

void AC_RabbitBase::BeginPlay()
{
	Super::BeginPlay();

	//_sensor->SetTraceDebugParams(true);
}



