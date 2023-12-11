// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasks/BTT_Melee.h"

#include "Libraries/C_FuncLibrary.h"

#include <Kismet/GameplayStatics.h>
#include <AIController.h>

UBTT_Melee::UBTT_Melee()
{
	bNotifyTick = true;
	NodeName = "Melee";
}

EBTNodeResult::Type UBTT_Melee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::InProgress;
}

void UBTT_Melee::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp,  NodeMemory, DeltaSeconds);

	auto pawn = OwnerComp.GetAIOwner()->GetPawn();
	FVector start = pawn->GetActorLocation();
	FVector dir = pawn->GetActorForwardVector();
	FVector end = C_FuncLibrary::CalcRay(start, dir, 60.f);

	FTraceDebugParams debug(true);
	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(pawn);
	FHitResult result;
	bool hit = C_FuncLibrary::LineTraceByProfile(GetWorld(), result, start, end, "Bullet", debug, queryParams);
	if (hit)
	{
		UGameplayStatics::ApplyDamage(result.GetActor(), 1.f, nullptr, pawn, nullptr);
	}
}
