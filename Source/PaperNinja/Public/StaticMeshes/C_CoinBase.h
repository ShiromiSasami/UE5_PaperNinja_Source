// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticMeshes/C_Pickup.h"
#include "C_CoinBase.generated.h"

/**
 * コインの基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_CoinBase : public AC_Pickup
{
	GENERATED_BODY()

public:
	AC_CoinBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ObtainedImpl(APawn* player, APlayerController* controller) override;

public:
	/// <summary>
	/// コインが飛んでスポーンするかの設定
	/// </summary>
	FORCEINLINE void EnableTossed() { _tossed = true; };

	/// <summary>
	/// コインが落ち着く制限値の設定
	/// </summary>
	/// <param name="value">制限値</param>
	FORCEINLINE void SetSleepThreshold(float value) { _sleepThreshold = value; };

	/// <summary>
	/// コインのトス運動の初速ベクトルの設定
	/// </summary>
	/// <param name="value">初速ベクトル</param>
	FORCEINLINE void SetTossVelocity(FVector value) { _tossVelocity = value; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class URotatingMovementComponent> _rotatingMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "トス運動の速度ベクトル"))
	FVector _tossVelocity;
	UPROPERTY(EditAnywhere)
	bool _tossed;
	UPROPERTY(EditAnywhere)
	float _sleepThreshold;

	UPROPERTY(EditAnywhere)
	FVector Gravity;

	TObjectPtr <class UNiagaraSystem> _spawnNiagara;
};
