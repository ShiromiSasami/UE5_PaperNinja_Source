// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "C_GateBase.generated.h"

/**
 * ゲートの基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_GateBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_GateBase();
	~AC_GateBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/// <summary>
	/// ゲートの開閉タイムライン処理
	/// </summary>
	/// <param name="vec">位置/param>
	UFUNCTION()
	void GateTimelineStep(FVector vec);

public:
	/// <summary>
	/// ゲートを開く
	/// </summary>
	inline void Open() { _gateTimeline->Play(); }

	/// <summary>
	/// ゲートを閉じる
	/// </summary>
	inline void Close() { _gateTimeline->Reverse(); };

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UArrowComponent> _arrow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UStaticMeshComponent> _gateR;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	TObjectPtr<class UStaticMeshComponent> _gateL;

	FTimeline* _gateTimeline;
};
