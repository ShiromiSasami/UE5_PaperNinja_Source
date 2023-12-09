// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "C_SpikesBase.generated.h"

/**
 * 
 */
UCLASS()
class PAPERNINJA_API AC_SpikesBase : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AC_SpikesBase();

private:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
