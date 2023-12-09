// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "C_Pickup.generated.h"

DECLARE_DELEGATE_OneParam(FObtainedSignature, AC_Pickup*);

/**
 * 取得Actorの抽象クラス
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
/// Triggerを任意のコリジョンクラスにキャストして生成する
/// コンストラクタでのみ使用可能
/// </summary>
/// <typeparam name="T"> 任意のコリジョンクラス </typeparam>
/// <param name="name"> エディタ上に公開されるTriggerの名前 </param>
/// <returns> キャスト後のTrigger </returns>
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
