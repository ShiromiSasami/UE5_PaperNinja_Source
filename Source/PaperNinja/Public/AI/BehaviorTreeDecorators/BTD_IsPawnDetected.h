// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTD_IsPawnDetected.generated.h"

/**
 * �Y����APawn��Key�ɒ��g�����邩�m�F����f�R���[�^�[
 */
UCLASS()
class PAPERNINJA_API UBTD_IsPawnDetected : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTD_IsPawnDetected();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
