// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasks/BTT_PopPatrolPoint.h"

#include "AI/C_AIControllerBase.h"

UBTT_PopPatrolPoint::UBTT_PopPatrolPoint()
{
	NodeName = "PopPatrolPoint";
}

EBTNodeResult::Type UBTT_PopPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	if (!AIController) { return EBTNodeResult::Failed; }

	auto aiController = Cast<AC_AIControllerBase>(AIController);
	if (!aiController) { return EBTNodeResult::Failed; }

	aiController->PopPatrolPoint();

	return EBTNodeResult::Succeeded;
}
