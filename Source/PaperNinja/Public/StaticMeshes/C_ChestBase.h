// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticMeshes/C_Pickup.h"
#include "C_ChestBase.generated.h"

/**
 * �󔠂̊��N���X
 */
UCLASS()
class PAPERNINJA_API AC_ChestBase : public AC_Pickup
{
	GENERATED_BODY()

public:
	AC_ChestBase();

protected:
	/// <summary>
	/// �v���C���[�ڐG�C�x���g
	/// </summary>
	/// <param name="player">�v���C���[�|�[��</param>
	/// <param name="controller">�v���C���[�R���g���[���[</param>
	virtual void ObtainedImpl(APawn* player, APlayerController* controller) override;

private:
	UClass* CoinClass;
	TObjectPtr<class UNiagaraComponent> _fx;
};
