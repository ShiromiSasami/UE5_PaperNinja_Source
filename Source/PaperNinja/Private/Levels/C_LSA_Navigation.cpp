// Fill out your copyright notice in the Description page of Project Settings.

#include "Levels/C_LSA_Navigation.h"

//#include "PaperNinja/DebugTools.h"
#include "Characters/C_RabbitBase.h"
#include "Structures/PatrolPoint.h"

#include <EngineUtils.h>
#include <Engine/TargetPoint.h>
#include <AIController.h>


AC_LSA_Navigation::AC_LSA_Navigation()
{
    _patrolPoints.Reset(4);
}

void AC_LSA_Navigation::BeginPlay()
{
    /*if (_enemy)
    {
        AAIController* aiController = Cast<AAIController>(_enemy->GetController());
        if (aiController && _patrolPoints[0].TargetPoint)
        {
            FAIRequestID requestID = aiController->MoveToLocation(_patrolPoints[0].TargetPoint->GetActorLocation());
            if (requestID.IsValid())
            {
                aiController->ReceiveMoveCompleted.AddDynamic(this, &AC_LSA_Navigation::MoveCompleted);
            }
        }
    }*/
}

void AC_LSA_Navigation::MoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    /*if (Result == EPathFollowingResult::Type::Success)
    {
        if (_patrolPoints.IsEmpty()) { return; }
        FPatrolPoint point = _patrolPoints[0];
        _patrolPoints.RemoveAt(0);
        _patrolPoints.Add(point);

        if (_enemy)
        {
            FTimerHandle handle;
            GetWorldTimerManager().SetTimer(
                handle,
                [this] {
                    AAIController* aiController = Cast<AAIController>(_enemy->GetController());
                    if (aiController)
                    {
                        FAIRequestID requestID = aiController->MoveToLocation(_patrolPoints[0].TargetPoint->GetActorLocation());
                    }
                },
                _patrolPoints[0].WaitTime, 
                false
            );
        }
    }*/
}
