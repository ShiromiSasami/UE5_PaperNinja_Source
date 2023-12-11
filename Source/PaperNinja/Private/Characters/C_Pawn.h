// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Components/C_AC_SensorBase.h"
#include "Structures/PatrolPoint.h"
#include "C_Pawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FJumpedSignature, AC_Pawn, OnPawnJumped, AC_Pawn*, actor);

/**ゲーム内Characterの抽象クラス
 *
 */
UCLASS()
class AC_Pawn : public ACharacter
{
	GENERATED_BODY()

public:
	AC_Pawn();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:
	/// <summary>
	/// ジャンプ時の処理
	/// </summary>
	virtual void OnJumped_Implementation() override;

	bool BeginSprint();
	bool EndSprint();

#pragma region InlineFunction
	/// <summary>
	/// 加速状態取得
	/// </summary>
	/// <returns>加速状態の有無</returns>
	FORCEINLINE bool IsSprinting() const { return bIsSprinting; };

	/// <summary>
	/// センサーの取得
	/// </summary>
	/// <returns>センサーのポインタ</returns>
	FORCEINLINE UC_AC_SensorBase* GetSensor() const { return _sensor; };

	/// <summary>
	/// パトロール位置の取得
	/// </summary>
	/// <returns>パトロール位置の配列</returns>
	inline TArray<FPatrolPoint> GetPatrolPoints() const { return _patrolPoints; };

	/// <summary>
	/// 現在の足元のアクターを取得
	/// </summary>
	/// <returns>アクターのポインタ</returns>
	inline AActor* GetCurrentFloor() const
	{
		FHitResult rusult = GetCharacterMovement()->CurrentFloor.HitResult;
		return rusult.GetActor();
	};
#pragma endregion
	/// <summary>
	/// ジャンプ時のデリゲート
	/// </summary>
	/// <param name="actor">ジャンプしたアクター</param>
	FJumpedSignature OnPawnJumped;
protected:
	UPROPERTY(EditAnywhere)
	TArray<FPatrolPoint> _patrolPoints;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> _weaponMeshAsset;
	TObjectPtr<UStaticMeshComponent> _weaponMesh;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UC_AC_SensorBase> _sensor;

private:
	UPROPERTY(EditAnywhere)
	bool bIsSprinting;

	TObjectPtr <AActor> _lastFloor;
	TObjectPtr <UCurveFloat> _acceleCurve;
	TObjectPtr <UCurveFloat> _rotRateCurve;

protected:
	inline static const FFloat16 MAX_SPRINT_SPEED = 200.f;
	inline static const FFloat16 MAX_WALK_SPEED = 75.f;
};
