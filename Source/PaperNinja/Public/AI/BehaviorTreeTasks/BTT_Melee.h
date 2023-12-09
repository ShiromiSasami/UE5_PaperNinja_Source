// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Melee.generated.h"

/**
 * çUåÇÇ∑ÇÈÉ^ÉXÉN
 */
UCLASS()
class PAPERNINJA_API UBTT_Melee : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_Melee();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
