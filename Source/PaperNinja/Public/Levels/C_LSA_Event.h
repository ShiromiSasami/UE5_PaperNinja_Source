// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "C_LSA_Event.generated.h"

/**
 * Eventレベルのレベルスクリプトアクター
 */
UCLASS()
class PAPERNINJA_API AC_LSA_Event : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AC_LSA_Event();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// Gate1コインを取得したときのイベント
	/// </summary>
	/// <param name="coin">取得したコイン</param>
	UFUNCTION()
	void OnGate1CoinObtained(AC_CoinBase* coin);

	/// <summary>
	/// Switchの状態が変わったときのイベント
	/// </summary>
	/// <param name="switchActor">変わったスイッチ</param>
	UFUNCTION()
	void OnSwitchChanged(class AC_SwitchBase* switchActor);

	/// <summary>
	/// ボーナスコインを取得したときのイベント
	/// </summary>
	/// <param name="coin">取得したコイン</param>
	UFUNCTION()
	void OnBonusCoinObtained(class AC_CoinBase* coin);

	/// <summary>
	/// コイン生成の非同期ループの定期処理
	/// </summary>
	/// <param name="index">生成した要素のindex</param>
	UFUNCTION()
	void SpawnCoinLoopBody(int index);

	/// <summary>
	/// コイン生成の非同期ループの完了処理
	/// </summary>
	/// <param name="index">生成数</param>
	UFUNCTION()
	void SpawnCoinCompleted(int index);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AC_GateBase> _gate0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class AC_CoinBase>> _gate1Coins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AC_GateBase> _gate1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class AC_SwitchBase>> _gate2Switches;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AC_GateBase> _gate2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<class ATargetPoint>> _bonusCoinPoints;
	TArray<TObjectPtr<class AC_CoinBase>> _spawnedCoins;
};
