// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasks/BTT_GoToPatrol.h"

#include "AI/C_AIControllerBase.h"

UBTT_GoToPatrol::UBTT_GoToPatrol()
{
}

EBTNodeResult::Type UBTT_GoToPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) { return EBTNodeResult::Failed; }

    auto* aiController = Cast<AC_AIControllerBase>(AIController);
    if (!aiController) { return EBTNodeResult::Failed; }

    aiController->MoveToPatrolPoint();

    return EBTNodeResult::Succeeded;
}
