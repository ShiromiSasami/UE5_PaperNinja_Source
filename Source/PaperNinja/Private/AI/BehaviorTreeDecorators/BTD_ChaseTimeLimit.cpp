// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeDecorators/BTD_ChaseTimeLimit.h"

#include "Characters/C_Pawn.h"
#include "Components/C_AC_SensorBase.h"
#include "Libraries/C_FuncLibrary.h"
#include "PaperNinja/DebugTools.h"

#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>

UBTD_ChaseTimeLimit::UBTD_ChaseTimeLimit()
	:_timeLimit(5.f)
{
	bNotifyTick = true;
	NodeName = "ChaseTimeLimit";
	FlowAbortMode = EBTFlowAbortMode::Self;
	BlackboardKey.SelectedKeyName = FName("TargetPawn");
	BlackboardKey.SelectedKeyType = APawn::StaticClass();
}

void UBTD_ChaseTimeLimit::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	_lastSeenTime = 0.f;
}

void UBTD_ChaseTimeLimit::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);

	_lastSeenTime = 0.f;
}

void UBTD_ChaseTimeLimit::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	CheckConditionValue(OwnerComp);

	auto pawn = Cast<AC_Pawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!pawn) { return; }

	auto obj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName);
	if(!obj) { return; }

	if (pawn->GetSensor()->CanSeeActor(Cast<AActor>(obj)))
	{
		_lastSeenTime = GetWorld()->GetTimeSeconds();
	}
}

void UBTD_ChaseTimeLimit::CheckConditionValue(UBehaviorTreeComponent& OwnerComp)
{
 	float curretTime = GetWorld()->GetTimeSeconds() - _lastSeenTime;
	if (_lastSeenTime == 0.f || curretTime <= _timeLimit) { return; }

	OwnerComp.RequestExecution(this);
}
