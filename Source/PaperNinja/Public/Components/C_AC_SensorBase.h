// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Libraries/C_FuncLibrary.h"
#include "C_AC_SensorBase.generated.h"

/**
 *	�Z���T�[�R���|�[�l���g�N���X
 */
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PAPERNINJA_API UC_AC_SensorBase : public USceneComponent
{
	GENERATED_BODY()

public:	
	UC_AC_SensorBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/// <summary>
	/// �f�o�b�O�ݒ�
	///���R���X�g���N�^���ɐݒ肵�Ă����f����܂���
	///BeginPlay�ȍ~�ōs���Ă�������
	/// </summary>
	/// <param name="params">�f�o�b�O�ݒ�\����</param>
	FORCEINLINE void SetTraceDebugParams(const struct FTraceDebugParams& params) { _traceDebugParams = params; }

	/// <summary>
	/// ���m���ʂ��擾����
	/// </summary>
	/// <returns>�������A�N�^�[, ���������̗L��</returns>
	std::tuple<TArray<AActor*>, bool> CheckSensor();

	/// <summary>
	/// �Ώۂ̃A�N�^�[������ɓ����Ă��邩�m�F����
	/// </summary>
	/// <param name="tagetActor">�m�F����A�N�^�[</param>
	/// <returns>����ɓ����Ă��邩�̗L��</returns>
	bool CanSeeActor(AActor* tagetActor);

	/// <summary>
	/// ��(SoundEmitter)�����m���A���̈ʒu���擾����
	/// </summary>
	/// <param name="locations">���m�����ʒu</param>
	/// <returns>���m�̗L��</returns>
	bool DetectSound(TArray<FVector>& locations);

private:
	/// <summary>
	/// �Ώۂ̈ʒu������ɓ����Ă��邩�m�F����
	/// </summary>
	/// <param name="tagetLocation">�m�F����ʒu</param>
	/// <returns>�����Ă��邩�̌���</returns>
	bool IsInSight(FVector tagetLocation);

protected:
	UPROPERTY(EditAnywhere)
	float _sightLength;
	UPROPERTY(EditAnywhere)
	float _yawAngle;
	UPROPERTY(EditAnywhere)
	float _pitchAngle;
	UPROPERTY(EditAnywhere)
	float _soundRadius;

	FTraceDebugParams _traceDebugParams;
	FCollisionQueryParams _queryParams;
};
