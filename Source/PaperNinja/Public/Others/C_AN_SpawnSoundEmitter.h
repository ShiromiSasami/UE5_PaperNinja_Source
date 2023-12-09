// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "C_AN_SpawnSoundEmitter.generated.h"

/**
 * 足音を出すアニメーション通知
 */
UCLASS()
class PAPERNINJA_API UC_AN_SpawnSoundEmitter : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UC_AN_SpawnSoundEmitter();

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
};
