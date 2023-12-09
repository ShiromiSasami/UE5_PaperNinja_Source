// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticMeshes/C_Pickup.h"
#include "C_CoinBase.generated.h"

/**
 * �R�C���̊��N���X
 */
UCLASS()
class PAPERNINJA_API AC_CoinBase : public AC_Pickup
{
	GENERATED_BODY()

public:
	AC_CoinBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ObtainedImpl(APawn* player, APlayerController* controller) override;

public:
	/// <summary>
	/// �R�C�������ŃX�|�[�����邩�̐ݒ�
	/// </summary>
	FORCEINLINE void EnableTossed() { _tossed = true; };

	/// <summary>
	/// �R�C�����������������l�̐ݒ�
	/// </summary>
	/// <param name="value">�����l</param>
	FORCEINLINE void SetSleepThreshold(float value) { _sleepThreshold = value; };

	/// <summary>
	/// �R�C���̃g�X�^���̏����x�N�g���̐ݒ�
	/// </summary>
	/// <param name="value">�����x�N�g��</param>
	FORCEINLINE void SetTossVelocity(FVector value) { _tossVelocity = value; };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class URotatingMovementComponent> _rotatingMovement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "�g�X�^���̑��x�x�N�g��"))
	FVector _tossVelocity;
	UPROPERTY(EditAnywhere)
	bool _tossed;
	UPROPERTY(EditAnywhere)
	float _sleepThreshold;

	UPROPERTY(EditAnywhere)
	FVector Gravity;

	TObjectPtr <class UNiagaraSystem> _spawnNiagara;
};
