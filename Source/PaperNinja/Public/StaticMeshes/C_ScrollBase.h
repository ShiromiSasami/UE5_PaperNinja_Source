// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticMeshes/C_Pickup.h"
#include "C_ScrollBase.generated.h"

/**
 * �����̊��N���X
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
	/// �擾�\��Ԃ����f
	/// </summary>
	/// <param name="pawn">�v���C���[�|�[��</param>
	/// <param name="playerController">�v���C���[�R���g���[���[<</param>
	/// <returns>�\���̗L��</returns>
	virtual bool CanBeObtained(APawn* pawn, APlayerController* playerController) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _aura;
};
