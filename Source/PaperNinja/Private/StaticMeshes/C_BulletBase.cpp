// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_BulletBase.h"

#include "Libraries/C_FuncLibrary.h"

#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <Materials/MaterialInstanceConstant.h>
#include <Materials/MaterialInstanceDynamic.h>
#include <EngineUtils.h>

AC_BulletBase::AC_BulletBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
	if (const auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Engine/BasicShapes/Sphere.Sphere")))
	{
		const auto mesh = GetStaticMeshComponent();
		mesh->SetStaticMesh(MeshAsset);
		mesh->SetRelativeScale3D(FVector(0.1, 0.1, 0.1));
		mesh->SetNotifyRigidBodyCollision(true);
		mesh->SetUseCCD(true);
		mesh->SetCollisionProfileName("Bullet");
	}

	InitialLifeSpan = LIFE_SPAN_COUNT;
}

void AC_BulletBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if(const auto MaterialAsset = LoadObject<UMaterialInstanceConstant>(NULL, TEXT("/Game/Materials/MI_Bullet.MI_Bullet")))
	{
		_bulletMI = GetStaticMeshComponent()->CreateDynamicMaterialInstance(0, MaterialAsset);
		_bulletMI->SetVectorParameterValue("EmissiveColor", _bulletColor);
	}
}

void AC_BulletBase::BeginPlay()
{
	Super::BeginPlay();

	const auto mesh = GetStaticMeshComponent();
	mesh->SetSimulatePhysics(true);
	mesh->SetMassOverrideInKg(NAME_None, 3.f, true);
	

	GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &AC_BulletBase::ComponentHit);

	GetStaticMeshComponent()->AddImpulse(GetActorForwardVector() * BULLET_INITIAL_SPEED, NAME_None, true);
	
}

void AC_BulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetStaticMeshComponent()->AddForce(FMath::Lerp(FVector(0,0,980), FVector::ZeroVector, AlphaScale), NAME_None, true);
}

void AC_BulletBase::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	SetActorTickEnabled(false);
	GetStaticMeshComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	_bulletMI->SetScalarParameterValue("EmissiveIntensity", 0);

	if (!C_FuncLibrary::IsPlayerPawn(OtherActor)) { return; }

	UGameplayStatics::ApplyDamage(OtherActor, 1.f, nullptr, this, nullptr);
}
