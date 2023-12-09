// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Engine/TargetPoint.h>
#include "PatrolPoint.generated.h"

/**
 * パトロール位置情報の構造体
 */
USTRUCT(BlueprintType)
struct FPatrolPoint
{
	GENERATED_USTRUCT_BODY()

	/// <summary>
	/// パトロール位置
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATargetPoint* TargetPoint;

	/// <summary>
	/// 待機時間
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaitTime;

	FPatrolPoint()
	{
		TargetPoint = nullptr;
		WaitTime = 2.0;
	}
}; 

