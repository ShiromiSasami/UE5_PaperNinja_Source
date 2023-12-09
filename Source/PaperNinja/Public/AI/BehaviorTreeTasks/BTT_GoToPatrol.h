// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GoToPatrol.generated.h"

/**
 * パトロール位置に移動するタスク
 */
UCLASS()
class PAPERNINJA_API UBTT_GoToPatrol : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTT_GoToPatrol();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
