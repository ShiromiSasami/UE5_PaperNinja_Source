// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Structures/PatrolPoint.h"
#include "C_AIControllerBase.generated.h"

/**
 * AIController�̊��N���X
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
	/// �p�g���[���ʒu�̎擾
	/// </summary>
	/// <returns>���݂̖ڕW�p�g���[���ʒu</returns>
	FORCEINLINE FPatrolPoint GetPatrolPoint()
	{
		return _patrolPoints[0];
	}

	/// <summary>
	/// �p�g���[���ʒu�ֈړ�
	/// </summary>
	inline void MoveToPatrolPoint()
	{
		MoveToLocation(_patrolPoints[0].TargetPoint->GetActorLocation());
	}

	/// <summary>
	/// �p�g���[���ʒu�̍X�V
	/// </summary>
	void PopPatrolPoint();

private:
	TArray<FPatrolPoint> _patrolPoints;
	TObjectPtr<UBehaviorTree> _patrolTree;
};
