// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "C_AN_SpawnFootSmoke.generated.h"

/**
 * 
 */
UCLASS()
class PAPERNINJA_API UC_AN_SpawnFootSmoke : public UAnimNotify
{
	GENERATED_BODY()
public:
	UC_AN_SpawnFootSmoke();

private:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UNiagaraSystem> _spawnNiagara;
	UPROPERTY(EditAnywhere)
	FName _soketName;
};
