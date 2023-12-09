// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticMeshes/C_Pickup.h"
#include "C_ChestBase.generated.h"

/**
 * 宝箱の基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_ChestBase : public AC_Pickup
{
	GENERATED_BODY()

public:
	AC_ChestBase();

protected:
	/// <summary>
	/// プレイヤー接触イベント
	/// </summary>
	/// <param name="player">プレイヤーポーン</param>
	/// <param name="controller">プレイヤーコントローラー</param>
	virtual void ObtainedImpl(APawn* player, APlayerController* controller) override;

private:
	UClass* CoinClass;
	TObjectPtr<class UNiagaraComponent> _fx;
};
