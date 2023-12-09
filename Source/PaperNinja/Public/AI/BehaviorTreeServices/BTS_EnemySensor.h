// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_EnemySensor.generated.h"

/**
 * AIのプレイヤー視認サービス
 */
UCLASS()
class PAPERNINJA_API UBTS_EnemySensor : public UBTService
{
	GENERATED_BODY()
public:
	UBTS_EnemySensor();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector TargetActorKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SoundPointKey;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector SoundDetectKey;
};
