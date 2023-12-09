// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Structures/PatrolPoint.h"
#include "C_AIControllerBase.generated.h"

/**
 * AIControllerの基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_AIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AC_AIControllerBase();

private:
	virtual void BeginPlay() override;
	/*virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);*/

	virtual void OnPossess(APawn* InPawn) override;

public:
	/// <summary>
	/// パトロール位置の取得
	/// </summary>
	/// <returns>現在の目標パトロール位置</returns>
	FORCEINLINE FPatrolPoint GetPatrolPoint()
	{
		return _patrolPoints[0];
	}

	/// <summary>
	/// パトロール位置へ移動
	/// </summary>
	inline void MoveToPatrolPoint()
	{
		MoveToLocation(_patrolPoints[0].TargetPoint->GetActorLocation());
	}

	/// <summary>
	/// パトロール位置の更新
	/// </summary>
	void PopPatrolPoint();

private:
	TArray<FPatrolPoint> _patrolPoints;
	TObjectPtr<UBehaviorTree> _patrolTree;
};
