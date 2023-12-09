// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerControllerBase.generated.h"

/**
 * プレイヤーコントローラーの基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AC_PlayerControllerBase();
	
private:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;

	/// <summary>
	/// 入力のセットアップ
	/// </summary>
	void SetupInput();

	/// <summary>
	/// ジャンプアクション処理
	/// </summary>
	/// <param name="value">入力値</param>
	void JumpAction(const struct FInputActionValue& value);

	/// <summary>
	/// プレイヤーポーンの削除時イベント
	/// </summary>
	/// <param name="actor">プレイヤーポーン</param>
	/// <param name="endPlayReason">削除要因</param>
	UFUNCTION()
	void OnPawnEndPlay(AActor* actor, EEndPlayReason::Type endPlayReason);

private:
	//入力用メンバ
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInputMappingContext> _imc;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UInputAction> _inputJump;
};
