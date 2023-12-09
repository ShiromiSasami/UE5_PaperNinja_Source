// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "C_LSA_Trigger.generated.h"

/**
 *  トリガーレベルのレベルスクリプト
 */
UCLASS()
class PAPERNINJA_API AC_LSA_Trigger : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AC_LSA_Trigger();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	UFUNCTION()
	void OnSpikesHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	void OnTriggerOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void OnTrampolineHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class AStaticMeshActor> _spikes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class ATriggerBox> _deathTrigger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class AC_RabbitBase> _enemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class AStaticMeshActor> _trampoline;
};
