// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_SpikesBase.h"

#include <Kismet/GameplayStatics.h>

AC_SpikesBase::AC_SpikesBase()
{
	static auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Kitbash/KSM_Spikes.KSM_Spikes'"));
	if (MeshAsset)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset);
	}
}

void AC_SpikesBase::BeginPlay()
{
	Super::BeginPlay();
	GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &AC_SpikesBase::ComponentHit);
}

void AC_SpikesBase::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, 1.f, nullptr, this, nullptr);
}
