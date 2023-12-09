// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Libraries/C_FuncLibrary.h"
#include "C_AC_SensorBase.generated.h"

/**
 *	センサーコンポーネントクラス
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PAPERNINJA_API UC_AC_SensorBase : public USceneComponent
{
	GENERATED_BODY()

public:	
	UC_AC_SensorBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/// <summary>
	/// デバッグ設定
	///※コンストラクタ時に設定しても反映されません
	///BeginPlay以降で行ってください
	/// </summary>
	/// <param name="params">デバッグ設定構造体</param>
	FORCEINLINE void SetTraceDebugParams(const struct FTraceDebugParams& params) { _traceDebugParams = params; }

	/// <summary>
	/// 感知結果を取得する
	/// </summary>
	/// <returns>見つけたアクター, 見つけたかの有無</returns>
	std::tuple<TArray<AActor*>, bool> CheckSensor();

	/// <summary>
	/// 対象のアクターが視野に入っているか確認する
	/// </summary>
	/// <param name="tagetActor">確認するアクター</param>
	/// <returns>視野に入っているかの有無</returns>
	bool CanSeeActor(AActor* tagetActor);

	/// <summary>
	/// 音(SoundEmitter)を感知し、その位置を取得する
	/// </summary>
	/// <param name="locations">感知した位置</param>
	/// <returns>感知の有無</returns>
	bool DetectSound(TArray<FVector>& locations);

private:
	/// <summary>
	/// 対象の位置が視野に入っているか確認する
	/// </summary>
	/// <param name="tagetLocation">確認する位置</param>
	/// <returns>入っているかの結果</returns>
	bool IsInSight(FVector tagetLocation);

protected:
	UPROPERTY(EditAnywhere)
	float _sightLength;
	UPROPERTY(EditAnywhere)
	float _yawAngle;
	UPROPERTY(EditAnywhere)
	float _pitchAngle;
	UPROPERTY(EditAnywhere)
	float _soundRadius;

	FTraceDebugParams _traceDebugParams;
	FCollisionQueryParams _queryParams;
};
