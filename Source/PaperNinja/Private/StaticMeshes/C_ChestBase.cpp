// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_ChestBase.h"

#include "StaticMeshes/C_CoinBase.h"

#include <Components/BoxComponent.h>
#include <Materials/MaterialInstanceConstant.h>
#include <UObject/ConstructorHelpers.h>
#include <NiagaraComponent.h>
#include <NiagaraSystem.h>


AC_ChestBase::AC_ChestBase()
	:_fx(CreateDefaultSubobject<UNiagaraComponent>("FX Component"))
{
	const auto mesh = GetStaticMeshComponent();
	const FString MeshPath = TEXT("/Game/Megascans/3D_Assets/Small_Wooden_Coffer_ucnhfgviw/S_Small_Wooden_Coffer_ucnhfgviw_lod3.S_Small_Wooden_Coffer_ucnhfgviw_lod3");
	if (const auto MeshAsset = LoadObject<UStaticMesh>(NULL, *MeshPath))
	{
		mesh->SetStaticMesh(MeshAsset);
		mesh->SetCanEverAffectNavigation(false);
	}

	const auto trigger = CreateTrigger<UBoxComponent>("BoxCollision");
	trigger->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	trigger->SetBoxExtent(FVector(25.f, 40.f, 25.f));

	if (const auto BPCoin = LoadClass<AActor>(NULL, TEXT("/Game/Blueprints/StaticMesh/BP_Coin.BP_Coin_c")))
	{
		CoinClass = BPCoin;
	}

	if (const auto FX = LoadObject<UNiagaraSystem>(NULL, TEXT("/Game/Particles/Niagara/FXS_Chest.FXS_Chest")))
	{
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
		if (const auto coin = GetWorld()->SpawnActor<AC_CoinBase>(CoinClass, GetActorTransform(), SpawnParams))
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
