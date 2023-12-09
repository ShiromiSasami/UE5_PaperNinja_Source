// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "C_PlayerStateBase.generated.h"

/**
 * �v���C���[�X�e�[�g�̊��N���X
 */
UCLASS()
class PAPERNINJA_API AC_PlayerStateBase : public APlayerState
{
	GENERATED_BODY()
	
public:
	AC_PlayerStateBase();

	/// <summary>
	/// �����R�C�������̐ݒ�
	/// </summary>
	/// <param name="num">����</param>
	void SetCoinNum(const int num);

	/// <summary>
	/// �����R�C�������̎擾
	/// </summary>
	/// <returns>������</returns>
	int GetCoinNum() const;

protected:
	UPROPERTY(EditAnywhere, meta = (ToolTip = "���@��������R�C���̖���"))
	int _numOfCoins;

};
