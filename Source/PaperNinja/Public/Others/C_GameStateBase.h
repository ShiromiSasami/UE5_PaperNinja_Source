// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_GameStateBase.generated.h"

/**
 * GameState�̊�b�N���X
 */
UCLASS()
class PAPERNINJA_API AC_GameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AC_GameStateBase();

private:
	virtual void BeginPlay() override;

public:
#pragma region InlineFunction

	/// <summary>
	/// _hasScrolls�̏�����
	/// </summary>
	/// <param name="size">�v�f��</param>
	FORCEINLINE void InitScrolls(const uint8 size)
	{
		if (size == 0) { return; }
		_hasScrolls.Init(false, size);
	};

	/// <summary>
	/// �X�N���[�����擾�������Ƃ��L�^
	/// </summary>
	/// <param name="index">�擾�����X�N���[���̃C���f�b�N�X</param>
	FORCEINLINE void ObtainScroll(const int index)
	{
		if (_hasScrolls.Num() <= index) { return; }
		_hasScrolls[index] = true;
	};

	/// <summary>
	/// �`�F�b�N�|�C���g��ݒ�
	/// </summary>
	/// <param name="point">�`�F�b�N�|�C���g</param>
	FORCEINLINE void SetCheckpoint(AActor* point) { _checkpoint = point; };

	/// <summary>
	/// �`�F�b�N�|�C���g���擾
	/// </summary>
	/// <returns>�`�F�b�N�|�C���g</returns>
	FORCEINLINE AActor* GetCheckpoint() const { return _checkpoint; };
#pragma endregion

	/// <summary>
	/// �X�e�[�W�N���A���������f
	/// </summary>
	/// <returns>�N���A�̗L��</returns>
	bool HasCompletedLevel() const;

protected:
	UPROPERTY(EditAnywhere)
	TArray<bool> _hasScrolls;
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> _checkpoint;
};
