// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/TimelineComponent.h"
#include "C_TurretBase.generated.h"

/**
 * �^���b�g�̊�b�N���X
 */
UCLASS()
class PAPERNINJA_API AC_TurretBase : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AC_TurretBase();
	~AC_TurretBase();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// �o�����̉�]�^�C�����C���̍X�V
	/// </summary>
	/// <param name="value">��]�l</param>
	UFUNCTION()
	void BarrelTimelineStep(float value);

	/// <summary>
	/// �e�e�̐F�ύX�^�C�����C���̍X�V
	/// </summary>
	/// <param name="color">�F</param>
	UFUNCTION()
	void BulletColorTimelineStep(FLinearColor color);

	/// <summary>
	/// �e�e���ˏ���
	/// </summary>
	UFUNCTION()
	void OnBeginFire();

	/// <summary>
	/// �e�e���˒�~����
	/// </summary>
	UFUNCTION()
	void OnStopFire();

	/// <summary>
	/// �^�C�����C���J�n����
	/// </summary>
	void StartFire();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UStaticMeshComponent> _barrelMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class URotatingMovementComponent> _rotating;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	int _fireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UC_AC_SensorBase> _sensor;

private:
	FTransform GetLocalSpread() { return FTransform(FRotator(0, FMath::RandRange(-10, 10), 0)); }

private:
	FTimeline* _fireControlTimeline;
	FColor _fireColor;
	FTimerHandle _fireTimerHandle;
	UClass* BulletClass;
};
