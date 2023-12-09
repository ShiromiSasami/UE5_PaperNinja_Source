// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_ChestBase.h"

#include "StaticMeshes/C_CoinBase.h"

#include <Components/BoxComponent.h>
#include <Materials/MaterialInstanceConstant.h>
#include <UObject/ConstructorHelpers.h>
#include <NiagaraComponent.h>
#include <NiagaraSystem.h>


AC_ChestBase::AC_ChestBase()
{
	static auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Megascans/3D_Assets/Small_Wooden_Coffer_ucnhfgviw/S_Small_Wooden_Coffer_ucnhfgviw_lod3.S_Small_Wooden_Coffer_ucnhfgviw_lod3'"));
	auto* mesh = GetStaticMeshComponent();
	if (MeshAsset)
	{
		mesh->SetStaticMesh(MeshAsset);
		mesh->SetCanEverAffectNavigation(false);
	}

	auto trigger = CreateTrigger<UBoxComponent>("BoxCollision");
	trigger->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	trigger->SetBoxExtent(FVector(25.f, 40.f, 25.f));

	static auto BPCoin = LoadClass<AActor>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/StaticMesh/BP_Coin.BP_Coin_c'"));
	if (BPCoin)
	{
		CoinClass = BPCoin;
	}

	static auto FX = LoadObject<UNiagaraSystem>(NULL, TEXT("/Script/Niagara.NiagaraSystem'/Game/Particles/Niagara/FXS_Chest.FXS_Chest'"));
	if (FX)
	{
		_fx = CreateDefaultSubobject<UNiagaraComponent>("FX Component");
		_fx->SetAsset(FX);
		_fx->SetupAttachment(mesh);
	}
}

void AC_ChestBase::ObtainedImpl(APawn* player, APlayerController* controller)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.bDeferConstruction = true;
	for (int i = 0; i < 10; ++i)
	{
		if (auto coin = GetWorld()->SpawnActor<AC_CoinBase>(CoinClass, GetActorTransform(), SpawnParams))
		{
			coin->SetSleepThreshold(0.f);
			coin->EnableTossed();
			FTransform dirTrans;
			dirTrans.SetRotation(FRotator(20, FMath::RandRange(0, 360), 0).Quaternion());
			FVector tossVelocity = dirTrans.TransformVector(FVector(0, 0, 400.f));
			coin->SetTossVelocity(tossVelocity);
			coin->FinishSpawning(GetActorTransform());
		}
	}
}
