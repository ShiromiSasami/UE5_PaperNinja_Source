// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "C_LSA_Event.generated.h"

/**
 * Event���x���̃��x���X�N���v�g�A�N�^�[
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
	/// Gate1�R�C�����擾�����Ƃ��̃C�x���g
	/// </summary>
	/// <param name="coin">�擾�����R�C��</param>
	UFUNCTION()
	void OnGate1CoinObtained(AC_CoinBase* coin);

	/// <summary>
	/// Switch�̏�Ԃ��ς�����Ƃ��̃C�x���g
	/// </summary>
	/// <param name="switchActor">�ς�����X�C�b�`</param>
	UFUNCTION()
	void OnSwitchChanged(class AC_SwitchBase* switchActor);

	/// <summary>
	/// �{�[�i�X�R�C�����擾�����Ƃ��̃C�x���g
	/// </summary>
	/// <param name="coin">�擾�����R�C��</param>
	UFUNCTION()
	void OnBonusCoinObtained(class AC_CoinBase* coin);

	/// <summary>
	/// �R�C�������̔񓯊����[�v�̒������
	/// </summary>
	/// <param name="index">���������v�f��index</param>
	UFUNCTION()
	void SpawnCoinLoopBody(int index);

	/// <summary>
	/// �R�C�������̔񓯊����[�v�̊�������
	/// </summary>
	/// <param name="index">������</param>
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
