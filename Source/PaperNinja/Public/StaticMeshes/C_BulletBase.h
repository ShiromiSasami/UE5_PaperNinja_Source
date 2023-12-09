// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "C_BulletBase.generated.h"

/**
 * 
 */
UCLASS()
class PAPERNINJA_API AC_BulletBase : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AC_BulletBase();

private:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	FORCEINLINE void SetBulletColor(const FColor color) 
	{
		_bulletColor = color;
	}

private:
	inline static const float VELOCITY_POWER = 600.f;
	inline static const float GRAVITY_SCALE = 0.2f;
	inline static const float BULLET_INITIAL_SPEED = 400.f;

protected:
	inline static const float LIFE_SPAN_COUNT = 10.0;
	UPROPERTY(EditAnywhere);
	float AlphaScale = 0.2;
	UPROPERTY(EditAnywhere);
	FColor _bulletColor;

	TObjectPtr<UMaterialInstanceDynamic> _bulletMI;
};
