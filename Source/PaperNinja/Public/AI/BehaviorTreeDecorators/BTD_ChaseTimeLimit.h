// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_ChaseTimeLimit.generated.h"

/**
 * �Ώۂ��������܂ł̌o�ߎ��Ԃ𔻒f�f�R���[�^�[
 */
UCLASS()
class PAPERNINJA_API UBTD_ChaseTimeLimit : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTD_ChaseTimeLimit();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
protected:
	/// <summary>
	/// �������Ă���̌o�ߎ��Ԃ𔻒f
	/// </summary>
	/// <param name="OwnerComp">���s��������BehaviorTree</param>
	void CheckConditionValue(UBehaviorTreeComponent& OwnerComp);

private:
	float _lastSeenTime;
	UPROPERTY(EditAnywhere)
	float _timeLimit;
};
