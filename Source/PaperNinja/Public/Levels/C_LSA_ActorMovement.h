// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "C_LSA_ActorMovement.generated.h"

/**
 * ActorMovementレベルのレベルスクリプトアクター
 */
UCLASS()
class PAPERNINJA_API AC_LSA_ActorMovement : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	AC_LSA_ActorMovement();

private:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class AStaticMeshActor> _levelBullet0;
};
