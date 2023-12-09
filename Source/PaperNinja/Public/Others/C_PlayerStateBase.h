// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "C_PlayerStateBase.generated.h"

/**
 * プレイヤーステートの基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_PlayerStateBase : public APlayerState
{
	GENERATED_BODY()
	
public:
	AC_PlayerStateBase();

	/// <summary>
	/// 所持コイン枚数の設定
	/// </summary>
	/// <param name="num">枚数</param>
	void SetCoinNum(const int num);

	/// <summary>
	/// 所持コイン枚数の取得
	/// </summary>
	/// <returns>所持数</returns>
	int GetCoinNum() const;

protected:
	UPROPERTY(EditAnywhere, meta = (ToolTip = "自機が取ったコインの枚数"))
	int _numOfCoins;

};
