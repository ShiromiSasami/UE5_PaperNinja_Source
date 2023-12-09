// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Floor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UFloor : public UInterface
{
	GENERATED_BODY()
};

/**
 * ポーンが乗った時の処理インターフェース
 */
class PAPERNINJA_API IFloor
{
	GENERATED_BODY()

public:
	/// <summary>
	/// ポーンが乗った時の処理(記述必須)
	/// </summary>
	/// <param name="pawn">乗っているPawn</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPawnOn(class	AC_Pawn* pawn);
	virtual void OnPawnOn_Implementation(class	AC_Pawn* pawn) = 0;

	/// <summary>
	/// ポーンが降りた時の処理(記述必須)
	/// </summary>
	/// <param name="pawn">乗っていたPawn</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPawnOff(class AC_Pawn* pawn);
	virtual void OnPawnOff_Implementation(class	AC_Pawn* pawn) = 0;
};
