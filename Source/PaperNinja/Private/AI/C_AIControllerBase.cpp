// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/C_AIControllerBase.h"

#include "Characters/C_Pawn.h"

#include <Engine/TargetPoint.h>
#include "BehaviorTree/BehaviorTree.h"

AC_AIControllerBase::AC_AIControllerBase()
{
    _patrolPoints.Empty();

    UBehaviorTree* PatrolTree = LoadObject<UBehaviorTree>(NULL, TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_Patrol.BT_Patrol'"));
    if (PatrolTree)
    {
        _patrolTree = PatrolTree;
    }
}

void AC_AIControllerBase::BeginPlay()
{
	Super::BeginPlay();

    if (!_patrolPoints.IsEmpty())
    {
        RunBehaviorTree(_patrolTree);
    }
}

//void AC_AIControllerBase::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
//{
//    Super::OnMoveCompleted(RequestID, Result);
//
//    if (Result.IsSuccess())
//    {
//        if (_patrolPoints.IsEmpty()) { return; }
//        
//        PopPatrolPoint();
//
//        FTimerHandle handle;
//        GetWorldTimerManager().SetTimer(
//            handle,
//            [this] {
//                MoveToLocation(_patrolPoints[0].TargetPoint->GetActorLocation());
//            },
//            _patrolPoints[0].WaitTime,
//            false
//        );
//    }
//}

void AC_AIControllerBase::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

	InPawn->SetCanBeDamaged(false);

    if (auto* pawn = Cast<AC_Pawn>(InPawn))
    {
        _patrolPoints = pawn->GetPatrolPoints();
    }
}

void AC_AIControllerBase::PopPatrolPoint()
{
    //PatrolPointの要素シフト
    FPatrolPoint point = _patrolPoints[0];
    _patrolPoints.RemoveAt(0);
    _patrolPoints.Add(point);
}
