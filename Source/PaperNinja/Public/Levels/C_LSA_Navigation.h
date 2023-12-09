// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "C_LSA_Navigation.generated.h"

/**
 * Navigationレベルのレベルスクリプトアクター
 */
UCLASS()
class PAPERNINJA_API AC_LSA_Navigation : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AC_LSA_Navigation();

private:
	virtual void BeginPlay() override;

private:
	/// <summary>
	/// 移動完了のコールバック(ReceiveMoveCompletedにバインド)
	/// </summary>
	/// <param name="RequestID">命令状態</param>
	/// <param name="Result">結果</param>
	UFUNCTION()
	void MoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AC_RabbitBase> _enemy;
	UPROPERTY(EditAnywhere)
	TArray<struct FPatrolPoint> _patrolPoints;
};
