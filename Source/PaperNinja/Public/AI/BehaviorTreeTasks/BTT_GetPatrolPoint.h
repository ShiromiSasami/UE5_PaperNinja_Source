// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetPatrolPoint.generated.h"

/**
 * パトロールポイントを取得するタスク
 */
UCLASS()
class PAPERNINJA_API UBTT_GetPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_GetPatrolPoint();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector _locationKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector _waitDurationKey;
};
