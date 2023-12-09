// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/TimelineComponent.h"
#include "C_TurretBase.generated.h"

/**
 * タレットの基礎クラス
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

	/// <summary>
	/// バレルの回転タイムラインの更新
	/// </summary>
	/// <param name="value">回転値</param>
	UFUNCTION()
	void BarrelTimelineStep(float value);

	/// <summary>
	/// 銃弾の色変更タイムラインの更新
	/// </summary>
	/// <param name="color">色</param>
	UFUNCTION()
	void BulletColorTimelineStep(FLinearColor color);

	/// <summary>
	/// 銃弾発射処理
	/// </summary>
	UFUNCTION()
	void OnBeginFire();

	/// <summary>
	/// 銃弾発射停止処理
	/// </summary>
	UFUNCTION()
	void OnStopFire();

	/// <summary>
	/// タイムライン開始処理
	/// </summary>
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
