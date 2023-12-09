// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Anim_NinjaBase.generated.h"

/**
 * 忍者のアニメーション基礎クラス
 */
UCLASS()
class PAPERNINJA_API UAnim_NinjaBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnim_NinjaBase();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasCompletedLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsInAir;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanJump;
};
