// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasks/BTT_GetPatrolPoint.h"

#include "AI/C_AIControllerBase.h"

#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Vector.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Float.h>

UBTT_GetPatrolPoint::UBTT_GetPatrolPoint()
{
    _locationKey.SelectedKeyName = FName("PatrolLocation");
    _locationKey.SelectedKeyType = UBlackboardKeyType_Vector::StaticClass();

    _waitDurationKey.SelectedKeyName = FName("PatrolWaitDuration");
    _waitDurationKey.SelectedKeyType = UBlackboardKeyType_Float::StaticClass();
    
}

EBTNodeResult::Type UBTT_GetPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController){ return EBTNodeResult::Failed; }

    auto aiController = Cast<AC_AIControllerBase>(AIController);
    if (!aiController) { return EBTNodeResult::Failed; }

    UBlackboardComponent* blackboardComp = OwnerComp.GetBlackboardComponent();
    blackboardComp->SetValueAsVector(_locationKey.SelectedKeyName, aiController->GetPatrolPoint().TargetPoint->GetActorLocation());
    blackboardComp->SetValueAsFloat(_waitDurationKey.SelectedKeyName, aiController->GetPatrolPoint().WaitTime);

    return EBTNodeResult::Succeeded;
}
