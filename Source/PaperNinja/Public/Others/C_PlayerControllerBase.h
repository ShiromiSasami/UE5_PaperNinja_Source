// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerControllerBase.generated.h"

/**
 * �v���C���[�R���g���[���[�̊��N���X
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
	/// ���͂̃Z�b�g�A�b�v
	/// </summary>
	void SetupInput();

	/// <summary>
	/// �W�����v�A�N�V��������
	/// </summary>
	/// <param name="value">���͒l</param>
	void JumpAction(const struct FInputActionValue& value);

	/// <summary>
	/// �v���C���[�|�[���̍폜���C�x���g
	/// </summary>
	/// <param name="actor">�v���C���[�|�[��</param>
	/// <param name="endPlayReason">�폜�v��</param>
	UFUNCTION()
	void OnPawnEndPlay(AActor* actor, EEndPlayReason::Type endPlayReason);

private:
	//���͗p�����o
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInputMappingContext> _imc;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UInputAction> _inputJump;
};
