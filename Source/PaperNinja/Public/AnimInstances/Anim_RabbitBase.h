// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim_RabbitBase.generated.h"

/**
 * ラビットのアニメーション基礎クラス
 */
UCLASS()
class PAPERNINJA_API UAnim_RabbitBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnim_RabbitBase();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bisSprint;
};
