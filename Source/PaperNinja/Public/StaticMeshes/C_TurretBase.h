// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/TimelineComponent.h"
#include "C_TurretBase.generated.h"

/**BPタレットの基礎クラス(BPに派生前提)
 * 
 */
UCLASS()
class PAPERNINJA_API AC_TurretBase : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AC_TurretBase();
	~AC_TurretBase();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void BarrelTimelineStep(float value);
	UFUNCTION()
	void BulletColorTimelineStep(FLinearColor color);
	UFUNCTION()
	void OnBeginFire();
	UFUNCTION()
	void OnStopFire();

	void StartFire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UStaticMeshComponent> _barrelMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class URotatingMovementComponent> _rotating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int _fireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UC_AC_SensorBase> _sensor;

private:
	FTransform GetLocalSpread() { return FTransform(FRotator(0, FMath::RandRange(-10, 10), 0)); }

private:
	FTimeline* _fireControlTimeline;
	FColor _fireColor;
	FTimerHandle _fireTimerHandle;
	UClass* BulletClass;
};
