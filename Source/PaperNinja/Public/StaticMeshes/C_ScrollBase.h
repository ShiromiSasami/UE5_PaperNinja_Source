// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticMeshes/C_Pickup.h"
#include "C_ScrollBase.generated.h"

/**
 * 巻物の基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_ScrollBase : public AC_Pickup
{
	GENERATED_BODY()

public:
	AC_ScrollBase();

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// 取得可能状態か判断
	/// </summary>
	/// <param name="pawn">プレイヤーポーン</param>
	/// <param name="playerController">プレイヤーコントローラー<</param>
	/// <returns>可能かの有無</returns>
	virtual bool CanBeObtained(APawn* pawn, APlayerController* playerController) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _aura;
};
