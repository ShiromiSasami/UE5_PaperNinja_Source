// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Pawn.h"
#include "C_NinjaBase.generated.h"

/**
 * 忍者の基礎クラス
 */

UCLASS()
class PAPERNINJA_API AC_NinjaBase : public AC_Pawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_NinjaBase();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	/// <summary>
	/// 自爆の入力
	/// </summary>
	/// <param name="value">入力値</param>
	void ForceKillAction(const struct FInputActionValue& value);

	/// <summary>
	/// 画面方向の入力
	/// </summary>
	/// <param name="value">入力値</param>
	void LookAction(const struct FInputActionValue& value);

	/// <summary>
	/// 移動方向の入力
	/// </summary>
	/// <param name="value">入力値</param>
	void MoveAction(const struct FInputActionValue& value);

	/// <summary>
	/// 加速の入力
	/// </summary>
	/// <param name="value">入力値</param>
	void SprintAction(const struct FInputActionValue& value);

private:
	inline static const float ARM_LENGTH = 1500.f;
	inline static const float FOV = 50.f;
	inline static const float CAPSULE_HALF_HIGHT = 44.f;
	inline static const float MAX_STEP_HEIGHT = 20.f;
	inline static const float ROTATION_RATE_ROLL = 180.f;
	inline static const float JUMP_Z_VELOCITY = 300.f;
	inline static const float AIR_CONTROL = 1.f;
	inline static const float PERCH_RADIUS_THRESHOLD = 25.f;
	inline static const float PERCH_ADDITIONAL_HEIGHT = 0.f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class USpringArmComponent> _springArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UCameraComponent> _camera;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UInputAction> _inputForceKill;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UInputAction> _inputLook;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UInputAction> _inputMove;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UInputAction> _inputSprint;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UNiagaraSystem> _fxTemplate;
	

	UPROPERTY(EditAnywhere)
	float LifeSpanCount = 5.0f;
	bool bDead;
};
