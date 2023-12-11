// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "C_Pickup.generated.h"

DECLARE_DELEGATE_OneParam(FObtainedSignature, AC_Pickup*);

/**
 * �擾Actor�̒��ۃN���X
 */
UCLASS(Abstract)
class AC_Pickup : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AC_Pickup();

protected:
	virtual void BeginPlay() override;

	/// <summary>
	/// �R���W�����̃I�[�o�[���b�v�C�x���g
	/// </summary>
	/// <param name="OverlappedComponent">�R���W�����R���|�[�l���g</param>
	/// <param name="OtherActor">�ڐG�����A�N�^�[</param>
	/// <param name="OtherComp">�ڐG�����R���|�[�l���g</param>
	/// <param name="OtherBodyIndex">�ڐG�����R���|�[�l���g</param>
	/// <param name="bFromSweep">�{�[���̃C���f�b�N�X</param>
	/// <param name="SweepResult">�Փˏ��</param>
	UFUNCTION()
	virtual void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/// <summary>
	/// �v���C���[���擾(�ڐG)�������̏���
	/// </summary>
	/// <param name="player">�v���C���[�|�[��</param>
	/// <param name="controller">�v���C���[�R���g���[���[</param>
	virtual void ObtainedImpl(APawn* player, APlayerController* controller) {};

	/// <summary>
	/// �擾(�ڐG)�\�����f
	/// </summary>
	/// <param name="pawn">�v���C���[�|�[��</param>
	/// <param name="playerController">�v���C���[�R���g���[���[</param>
	/// <returns></returns>
	virtual bool CanBeObtained(APawn* pawn, APlayerController* playerController);

	/*C++20�ȍ~�ł̓R���Z�v�g�𗘗p���ׂ�
	template<typename T>
	concept CollisionType = std::is_base_of_v<UPrimitiveComponent, T>;
	template<CollisionType T>*/
	/// <summary>
	/// Trigger��C�ӂ̃R���W�����N���X�ɃL���X�g���Đ�������
	/// �R���X�g���N�^�ł̂ݎg�p�\
	/// </summary>
	/// <typeparam name="T"> �C�ӂ̃R���W�����N���X </typeparam>
	/// <param name="name"> �G�f�B�^��Ɍ��J�����Trigger�̖��O </param>
	/// <returns> �L���X�g���Trigger </returns>
	template<typename T>
	T* CreateTrigger(const FName name);

public:

	FObtainedSignature OnObtained;

protected:
	TObjectPtr<UPrimitiveComponent> _trigger;
};


template<typename T>
T* AC_Pickup::CreateTrigger(const FName name)
{
	static_assert(std::is_base_of<UPrimitiveComponent, T>::value, "T must inherit from UPrimitiveComponent");

	T* trigger = CreateDefaultSubobject<T>(name);
	trigger->SetupAttachment(GetStaticMeshComponent());
	trigger->SetCollisionProfileName(TEXT("PickupMesh"));
	_trigger = trigger;

	return trigger;
}
