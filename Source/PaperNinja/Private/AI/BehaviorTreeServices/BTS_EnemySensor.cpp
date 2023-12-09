// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeServices/BTS_EnemySensor.h"

#include "Characters/C_Pawn.h"
#include "Components/C_AC_SensorBase.h"
#include "Libraries/C_FuncLibrary.h"

#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include <AIController.h>

UBTS_EnemySensor::UBTS_EnemySensor()
{
	NodeName = "EnemySensor";
	TargetActorKey.SelectedKeyName = FName("TargetPawn");
	TargetActorKey.SelectedKeyType = APawn::StaticClass();
	SoundPointKey.SelectedKeyName = FName("SoundPoint");
	SoundDetectKey.SelectedKeyName = FName("SoundDetected");
	Interval = 0.25f;
	RandomDeviation = 0.1f;
}

void UBTS_EnemySensor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (!BlackboardComp) { return; }
    BlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, nullptr);

	auto pawn = Cast<AC_Pawn>(OwnerComp.GetAIOwner()->GetPawn());
	if(!pawn) { return; }

	TArray<AActor*> hitActors = std::get<0>(pawn->GetSensor()->CheckSensor());
	for(auto* actor : hitActors)
	{
		if (C_FuncLibrary::IsPlayerPawn(actor))
		{
			BlackboardComp->SetValueAsObject(TargetActorKey.SelectedKeyName, actor);
			break;
		}
	}

	TArray<FVector> soundLocations;
	bool detected = pawn->GetSensor()->DetectSound(soundLocations);
	if (detected)
	{
		BlackboardComp->SetValueAsVector(SoundPointKey.SelectedKeyName, soundLocations[0]);
	}
	BlackboardComp->SetValueAsBool(SoundDetectKey.SelectedKeyName, detected);
}
