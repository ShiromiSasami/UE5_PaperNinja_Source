// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Floor.h"
#include <Engine/StaticMeshActor.h>
#include "C_SwitchBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FChangedSignature, AC_SwitchBase, OnChanged, AC_SwitchBase*, switchActor );

/**
 * �{�^���̊��N���X
 */
UCLASS()
class PAPERNINJA_API AC_SwitchBase : public AStaticMeshActor, public IFloor
{
	GENERATED_BODY()

public:
	AC_SwitchBase();

private:
	virtual void BeginPlay() override;

	/// <summary>
	/// �|�[������ɏ�������̏���
	/// </summary>
	/// <param name="pawn">�|�[��</param>
	virtual void OnPawnOn_Implementation(AC_Pawn* pawn) override;

	/// <summary>
	/// �|�[������ɍ~�肽���̏���
	/// </summary>
	/// <param name="pawn">�|�[��</param>
	virtual void OnPawnOff_Implementation(AC_Pawn* pawn) override;

public:
	/// <summary>
	/// �X�C�b�`���؂�ւ�������̃C�x���g
	/// </summary>
	/// <param name="switchActor">�؂�ւ�����X�C�b�`</param>
	FChangedSignature OnChanged;

	/// <summary>
	/// �I���I�t��Ԃ��擾
	/// </summary>
	/// <returns>���</returns>
	FORCEINLINE bool IsOn() const { return bIsOn; };

protected:
	TObjectPtr<class UMaterialInterface> _mOn;
	TObjectPtr<class UMaterialInterface> _mOff;

	bool bIsOn;
};
