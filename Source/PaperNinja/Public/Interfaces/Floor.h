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
 * �|�[������������̏����C���^�[�t�F�[�X
 */
class PAPERNINJA_API IFloor
{
	GENERATED_BODY()

public:
	/// <summary>
	/// �|�[������������̏���(�L�q�K�{)
	/// </summary>
	/// <param name="pawn">����Ă���Pawn</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPawnOn(class	AC_Pawn* pawn);
	virtual void OnPawnOn_Implementation(class	AC_Pawn* pawn) = 0;

	/// <summary>
	/// �|�[�����~�肽���̏���(�L�q�K�{)
	/// </summary>
	/// <param name="pawn">����Ă���Pawn</param>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnPawnOff(class AC_Pawn* pawn);
	virtual void OnPawnOff_Implementation(class	AC_Pawn* pawn) = 0;
};
