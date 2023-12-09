// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeDecorators/BTD_IsPawnDetected.h"

#include <BehaviorTree/BlackboardComponent.h>

UBTD_IsPawnDetected::UBTD_IsPawnDetected()
{
    FlowAbortMode = EBTFlowAbortMode::Type::LowerPriority;
    BlackboardKey.SelectedKeyName = FName("TargetPawn");
    BlackboardKey.SelectedKeyType = APawn::StaticClass();
}

bool UBTD_IsPawnDetected::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp)
    {
        AActor* ActorToCheck = Cast<AActor>(BlackboardComp->GetValueAsObject(BlackboardKey.SelectedKeyName));
        return (ActorToCheck != nullptr);
    }

    return false;
}
