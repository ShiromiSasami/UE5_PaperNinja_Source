// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Floor.h"
#include <GameFramework/Actor.h>
#include <Components/TimelineComponent.h>
#include "C_JumpCubeBase.generated.h"

/**
 * ジャンプキューブの基底クラス
 */
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

	/// <summary>
	/// 移動のブレンド値のタイムライン処理
	/// </summary>
	/// <param name="value">ブレンド値</param>
	UFUNCTION()
	void JumpCubeLiftTimelineStep(float value);

	/// <summary>
	/// オンオフの切り替え
	/// </summary>
	/// <param name="actor">プレイヤーポーン</param>
	UFUNCTION()
	void Toggle(AC_Pawn* actor);

public:
	/// <summary>
	/// オフ状態にする
	/// </summary>
	inline void LiftReset() {
		bIsPlayingForward = false;
		_liftTimeline->Reverse();
	};

	/// <summary>
	/// C_Pawn系のアクターが乗った時の処理
	/// </summary>
	/// <param name="pawn">ポーン</param>
	virtual void OnPawnOn_Implementation(AC_Pawn* pawn) override;

	/// <summary>
	/// C_Pawn系のアクターが降りた時の処理
	/// </summary>
	/// <param name="pawn">ポーン/param>
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
