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

	/// <summary>
	/// コリジョンのオーバーラップイベント
	/// </summary>
	/// <param name="OverlappedComponent">コリジョンコンポーネント</param>
	/// <param name="OtherActor">接触したアクター</param>
	/// <param name="OtherComp">接触したコンポーネント</param>
	/// <param name="OtherBodyIndex">接触したコンポーネント</param>
	/// <param name="bFromSweep">ボーンのインデックス</param>
	/// <param name="SweepResult">衝突情報</param>
	UFUNCTION()
	virtual void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	/// <summary>
	/// プレイヤーが取得(接触)した時の処理
	/// </summary>
	/// <param name="player">プレイヤーポーン</param>
	/// <param name="controller">プレイヤーコントローラー</param>
	virtual void ObtainedImpl(APawn* player, APlayerController* controller) {};

	/// <summary>
	/// 取得(接触)可能か判断
	/// </summary>
	/// <param name="pawn">プレイヤーポーン</param>
	/// <param name="playerController">プレイヤーコントローラー</param>
	/// <returns></returns>
	virtual bool CanBeObtained(APawn* pawn, APlayerController* playerController);

	/*C++20以降ではコンセプトを利用すべき
	template<typename T>
	concept CollisionType = std::is_base_of_v<UPrimitiveComponent, T>;
	template<CollisionType T>*/
	/// <summary>
	/// Triggerを任意のコリジョンクラスにキャストして生成する
	/// コンストラクタでのみ使用可能
	/// </summary>
	/// <typeparam name="T"> 任意のコリジョンクラス </typeparam>
	/// <param name="name"> エディタ上に公開されるTriggerの名前 </param>
	/// <returns> キャスト後のTrigger </returns>
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
