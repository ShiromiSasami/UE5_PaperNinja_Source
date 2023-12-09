// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/C_LSA_ActorMovement.h"

#include "Engine/StaticMeshActor.h"

AC_LSA_ActorMovement::AC_LSA_ActorMovement()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AC_LSA_ActorMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_levelBullet0)
	{
		FVector location = _levelBullet0->GetActorLocation();
		location.X += 20.f;
		_levelBullet0->SetActorLocation(location);
	}
}
