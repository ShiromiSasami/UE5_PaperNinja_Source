// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_CoinBase.h"

#include "Others/C_PlayerStateBase.h"
#include "PaperNinja/DebugTools.h"

#include <Components/SphereComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <NiagaraFunctionLibrary.h>
#include <NiagaraSystem.h>
#include <GameFramework/RotatingMovementComponent.h>


AC_CoinBase::AC_CoinBase()
	: _tossVelocity(0.f, 0.f, 400.f),
	_tossed(false),
	_sleepThreshold(10.f),
	Gravity(0.f, 0.f, -980.f)
{
	PrimaryActorTick.bCanEverTick = true;

	static auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Props/SM_Coin.SM_Coin'"));
	if (MeshAsset)
	{
		auto mesh = GetStaticMeshComponent();
		mesh->SetStaticMesh(MeshAsset);
		mesh->SetCanEverAffectNavigation(false);
		mesh->SetCollisionProfileName("Bullet");
		FCollisionResponseContainer CollisionResponse = mesh->GetCollisionResponseToChannels();
		CollisionResponse.SetResponse(ECC_Pawn, ECR_Ignore);
	}

	SetMobility(EComponentMobility::Movable);

	_rotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");

	auto* trigger = CreateTrigger<USphereComponent>("SphereCollision");
	trigger->SetRelativeLocation(FVector(0.f, 0.f, 25.f));

	static auto FX = LoadObject<UNiagaraSystem>(NULL, TEXT("/Script/Niagara.NiagaraSystem'/Game/Particles/Niagara/FXS_Pickup.FXS_Pickup'"));
	if (FX)
	{
		_spawnNiagara = FX;
	}
}

void AC_CoinBase::BeginPlay()
{
	Super::BeginPlay();

	if (_tossed)
	{
		_trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(
			handle,
			[this] {
				_trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
			},
			1.0f,
			false
		);
	}
}

void AC_CoinBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_tossed)
	{
		auto gravity = Gravity * DeltaTime;
		_tossVelocity = _tossVelocity + gravity;

		auto addVec = _tossVelocity * DeltaTime;
		FHitResult* result = new FHitResult();
		AddActorWorldOffset(addVec, true, result);
		if (result->bBlockingHit)
		{
			FVector reflectedVector = FMath::GetReflectionVector(_tossVelocity, result->Normal) * 0.8f;
			_tossVelocity = reflectedVector;
			if (reflectedVector.Length() < _sleepThreshold)
			{
				_tossed = false;
			}
		}
	}
}

void AC_CoinBase::ObtainedImpl(APawn* player, APlayerController* controller)
{
	if (auto state = Cast<AC_PlayerStateBase>(controller->PlayerState))
	{
		state->SetCoinNum(state->GetCoinNum() + 1);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _spawnNiagara, player->GetActorLocation());
	}
}
