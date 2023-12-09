// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Floor.h"
#include <GameFramework/Actor.h>
#include <Components/TimelineComponent.h>
#include "C_JumpCubeBase.generated.h"

UCLASS()
class PAPERNINJA_API AC_JumpCubeBase : public AActor, public IFloor
{
	GENERATED_BODY()
	
public:	
	AC_JumpCubeBase();
	~AC_JumpCubeBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void JumpCubeLiftTimelineStep(float value);

	UFUNCTION()
	void Toggle(AC_Pawn* actor);

public:
	inline void LiftReset() {
		bIsPlayingForward = false;
		_liftTimeline->Reverse();
	};

	virtual void OnPawnOn_Implementation(AC_Pawn* pawn) override;
	virtual void OnPawnOff_Implementation(AC_Pawn* pawn) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _cube;

	TObjectPtr<class UMaterialInterface> _mOff;
	TObjectPtr<class UMaterialInterface> _mOn;

private:
	FTransform _identity;
	UPROPERTY(EditAnywhere)
	FTransform _destTransform;
	FTransform _dummyCube;

	FTimeline* _liftTimeline;
	bool bIsPlayingForward;
};
