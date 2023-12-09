// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_GateBase.generated.h"

UCLASS()
class PAPERNINJA_API AC_GateBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_GateBase();
	~AC_GateBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void GateTimelineStep(FVector vec);

public:
	inline void Open() { _gateTimeline->Play(); }
	inline void Close() { _gateTimeline->Reverse(); };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UArrowComponent> _arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UStaticMeshComponent> _gateR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UStaticMeshComponent> _gateL;

	FTimeline* _gateTimeline;
};
