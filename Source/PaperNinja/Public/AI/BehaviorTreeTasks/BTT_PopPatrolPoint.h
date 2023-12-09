// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTT_PopPatrolPoint.generated.h"

/**
 *  �p�g���[���ʒu�̍X�V�^�X�N
 */
UCLASS()
class PAPERNINJA_API UBTT_PopPatrolPoint : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UBTT_PopPatrolPoint();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
