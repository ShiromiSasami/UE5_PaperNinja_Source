// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/TargetPoint.h>
#include "PatrolPoint.generated.h"

/**
 * �p�g���[���ʒu���̍\����
 */
USTRUCT(BlueprintType)
struct FPatrolPoint
{
	GENERATED_USTRUCT_BODY()

	/// <summary>
	/// �p�g���[���ʒu
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATargetPoint* TargetPoint;

	/// <summary>
	/// �ҋ@����
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaitTime;

	FPatrolPoint()
	{
		TargetPoint = nullptr;
		WaitTime = 2.0;
	}
}; 

