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

	//SkeletalMeshComponent�̏�����
	if (const auto MeshAsset = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/SK_Rabbit.SK_Rabbit")))
	{
		const auto mesh = GetMesh();
		mesh->SetSkeletalMeshAsset(Cast<USkeletalMesh>(MeshAsset));
		mesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -44.f), FRotator(0.f, -90.f, 0.f));

		//�A�j���[�V�����̐ݒ�
		mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		if (const auto ABPAsset = LoadClass<UAnimInstance>(NULL, TEXT("/Game/Animations/ABP_Rabbit.ABP_Rabbit_c")))
		{
			mesh->AnimClass = ABPAsset;
		}
	}

	//CapsuleComponent�̏�����
	GetCapsuleComponent()->SetCapsuleHalfHeight(44.f);
}

void AC_RabbitBase::BeginPlay()
{
	Super::BeginPlay();

	//_sensor->SetTraceDebugParams(true);
}



