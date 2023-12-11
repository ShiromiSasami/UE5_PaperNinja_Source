// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_TurretBase.h"

#include "PaperNinja/DebugTools.h"
#include "StaticMeshes/C_BulletBase.h"
#include "Components/C_AC_SensorBase.h"
#include "Libraries/C_FuncLibrary.h"

#include <GameFramework/RotatingMovementComponent.h>
#include <Curves/CurveLinearColor.h>
#include <UObject/ConstructorHelpers.h>


AC_TurretBase::AC_TurretBase()
	:_barrelMesh(CreateDefaultSubobject<UStaticMeshComponent>("Barrel"))
	, _rotating(CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement"))
	, _fireControlTimeline(new FTimeline())
	, _fireRate(10)
	, _fireColor(FColor::White)
	
{
	PrimaryActorTick.bCanEverTick = true;

	if (const auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Props/SM_Turret.SM_Turret")))
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset);
	}

	if (const auto BarrelMeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Props/SM_Turret_Barrel.SM_Turret_Barrel")))
	{
		_barrelMesh->SetStaticMesh(BarrelMeshAsset);
		_barrelMesh->SetupAttachment(GetStaticMeshComponent(), "BarrelAttachPoint");
		_barrelMesh->SetMobility(EComponentMobility::Movable);
	}

	_rotating->RotationRate = FRotator(0.f, 0.f, 0.f);

	//Timeline設定
	_fireControlTimeline->SetTimelineLength(4.f);
	if (const auto BarrelCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Game/Curves/BarrelCurve.BarrelCurve")))
	{
		FOnTimelineFloat BarrelTimelineStepFunc;
		BarrelTimelineStepFunc.BindUFunction(this, "BarrelTimelineStep");
		_fireControlTimeline->AddInterpFloat(BarrelCurve, BarrelTimelineStepFunc);
	}

	if (const auto BulletColorCurve = LoadObject<UCurveLinearColor>(NULL, TEXT("/Game/Curves/BulletColorCurve.BulletColorCurve")))
	{
		FOnTimelineLinearColor BulletColorTimelineStepFunc;
		BulletColorTimelineStepFunc.BindUFunction(this, "BulletColorTimelineStep");
		_fireControlTimeline->AddInterpLinearColor(BulletColorCurve, BulletColorTimelineStepFunc);
	}

	FOnTimelineEvent BeginFireEvent;
	BeginFireEvent.BindUFunction(this, FName("OnBeginFire"));
	_fireControlTimeline->AddEvent(1.f, BeginFireEvent);
	FOnTimelineEvent StopEndFireEvent;
	StopEndFireEvent.BindUFunction(this, FName("OnStopFire"));
	_fireControlTimeline->AddEvent(3.f, StopEndFireEvent);

	if (const auto BPBullet = LoadClass<AC_BulletBase>(NULL, TEXT("/Game/Blueprints/StaticMesh/BP_Bullet.BP_Bullet_c")))
	{
		BulletClass = BPBullet;
	}
	
	if (const auto BPSensor = LoadClass<USceneComponent>(NULL, TEXT("/Game/Blueprints/Components/BP_AC_Sensor.BP_AC_Sensor_c")))
	{
		_sensor = Cast<UC_AC_SensorBase>(CreateDefaultSubobject("SensorComponent", BPSensor, BPSensor, true, false));
		_sensor->SetupAttachment(GetStaticMeshComponent(), "Muzzle");
	}
}

AC_TurretBase::~AC_TurretBase()
{
	if (_fireControlTimeline)
	{
		_fireControlTimeline->Stop();
		delete _fireControlTimeline;
		_fireControlTimeline = nullptr;
	}
}

void AC_TurretBase::BeginPlay()
{
	Super::BeginPlay();

	_rotating->SetUpdatedComponent(_barrelMesh);
	//_sensor->SetTraceDebugParams(FTraceDebugParams(true, 0.f));
}

void AC_TurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_fireControlTimeline->IsPlaying())
	{
		_fireControlTimeline->TickTimeline(DeltaTime);
	}
	//1番目要素はセンサーヒットの有無
	if (std::get<1>(_sensor->CheckSensor()))
	{
		StartFire();
	}
	
}

void AC_TurretBase::BarrelTimelineStep(float value)
{
	_rotating->RotationRate = FRotator(0.f, 0.f, value);
}

void AC_TurretBase::BulletColorTimelineStep(FLinearColor color)
{
	_fireColor = color.ToFColor(false);
}

void AC_TurretBase::OnBeginFire()
{
	const float time = C_FuncLibrary::SafeDivide(1.f, (float)_fireRate);
	GetWorldTimerManager().SetTimer(
		_fireTimerHandle,
		[this] {
			FTransform bulletTrans = GetLocalSpread() * GetStaticMeshComponent()->GetSocketTransform("Muzzle");
			FActorSpawnParameters spwnParams;
			spwnParams.bDeferConstruction = true;
			auto bullet =  GetWorld()->SpawnActor<AC_BulletBase>(BulletClass, bulletTrans, spwnParams);
			bullet->SetBulletColor(_fireColor);
			bullet->FinishSpawning(bulletTrans);
		},
		time,
		true,
		time * -1.f
		);
}

void AC_TurretBase::OnStopFire()
{
	GetWorldTimerManager().ClearTimer(_fireTimerHandle);
}

void AC_TurretBase::StartFire()
{
	if (_fireControlTimeline->IsPlaying()) { return; }
	_fireControlTimeline->PlayFromStart();
}