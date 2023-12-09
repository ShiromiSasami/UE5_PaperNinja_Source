// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_GameStateBase.generated.h"

/**
 * GameStateの基礎クラス
 */
UCLASS()
class PAPERNINJA_API AC_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AC_GameStateBase();

private:
	virtual void BeginPlay() override;

public:
#pragma region InlineFunction

	/// <summary>
	/// _hasScrollsの初期化
	/// </summary>
	/// <param name="size">要素数</param>
	FORCEINLINE void InitScrolls(const uint8 size)
	{
		if (size == 0) { return; }
		_hasScrolls.Init(false, size);
	};

	/// <summary>
	/// スクロールを取得したことを記録
	/// </summary>
	/// <param name="index">取得したスクロールのインデックス</param>
	FORCEINLINE void ObtainScroll(const int index)
	{
		if (_hasScrolls.Num() <= index) { return; }
		_hasScrolls[index] = true;
	};

	/// <summary>
	/// チェックポイントを設定
	/// </summary>
	/// <param name="point">チェックポイント</param>
	FORCEINLINE void SetCheckpoint(AActor* point) { _checkpoint = point; };

	/// <summary>
	/// チェックポイントを取得
	/// </summary>
	/// <returns>チェックポイント</returns>
	FORCEINLINE AActor* GetCheckpoint() const { return _checkpoint; };
#pragma endregion

	/// <summary>
	/// ステージクリアしたか判断
	/// </summary>
	/// <returns>クリアの有無</returns>
	bool HasCompletedLevel() const;

protected:
	UPROPERTY(EditAnywhere)
	TArray<bool> _hasScrolls;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> _checkpoint;
};
