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

	UFUNCTION()
	virtual void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void ObtainedImpl(APawn* player, APlayerController* controller){};

	virtual bool CanBeObtained(APawn* pawn, APlayerController* playerController);

	template<typename T>
	T* CreateTrigger(const FName name);

public:

	FObtainedSignature OnObtained;

protected:
	TObjectPtr<UPrimitiveComponent> _trigger;
};

/// <summary>
/// Trigger��C�ӂ̃R���W�����N���X�ɃL���X�g���Đ�������
/// �R���X�g���N�^�ł̂ݎg�p�\
/// </summary>
/// <typeparam name="T"> �C�ӂ̃R���W�����N���X </typeparam>
/// <param name="name"> �G�f�B�^��Ɍ��J�����Trigger�̖��O </param>
/// <returns> �L���X�g���Trigger </returns>
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
