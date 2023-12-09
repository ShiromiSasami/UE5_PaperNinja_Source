// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "C_AC_SineCurveMovement.generated.h"

/**
 * サインカーブコンポーネント
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PAPERNINJA_API UC_AC_SineCurveMovement : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UC_AC_SineCurveMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	FVector _amplitude;
	UPROPERTY(EditAnywhere)
	FVector _period;
	UPROPERTY(EditAnywhere)
	FVector _phase;

	FVector _initialLocation;
};
