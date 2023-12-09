// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Floor.h"
#include <Engine/StaticMeshActor.h>
#include "C_SwitchBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FChangedSignature, AC_SwitchBase, OnChanged, AC_SwitchBase*, switchActor );

/**
 * ボタンの基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_SwitchBase : public AStaticMeshActor, public IFloor
{
	GENERATED_BODY()

public:
	AC_SwitchBase();

private:
	virtual void BeginPlay() override;

	/// <summary>
	/// ポーンが上に乗った時の処理
	/// </summary>
	/// <param name="pawn">ポーン</param>
	virtual void OnPawnOn_Implementation(AC_Pawn* pawn) override;

	/// <summary>
	/// ポーンが上に降りた時の処理
	/// </summary>
	/// <param name="pawn">ポーン</param>
	virtual void OnPawnOff_Implementation(AC_Pawn* pawn) override;

public:
	/// <summary>
	/// スイッチが切り替わった時のイベント
	/// </summary>
	/// <param name="switchActor">切り替わったスイッチ</param>
	FChangedSignature OnChanged;

	/// <summary>
	/// オンオフ状態を取得
	/// </summary>
	/// <returns>状態</returns>
	FORCEINLINE bool IsOn() const { return bIsOn; };

protected:
	TObjectPtr<class UMaterialInterface> _mOn;
	TObjectPtr<class UMaterialInterface> _mOff;

	bool bIsOn;
};
