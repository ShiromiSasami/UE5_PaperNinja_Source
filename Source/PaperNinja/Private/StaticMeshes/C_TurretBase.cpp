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
	:_fireRate(10),
	_fireColor(FColor::White)
	
{
	PrimaryActorTick.bCanEverTick = true;

	static auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Props/SM_Turret.SM_Turret'"));
	if (MeshAsset)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset);
	}

	static auto BarrelMeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Props/SM_Turret_Barrel.SM_Turret_Barrel'"));
	if (BarrelMeshAsset)
	{
		_barrelMesh = CreateDefaultSubobject<UStaticMeshComponent>("Barrel");
		_barrelMesh->SetStaticMesh(BarrelMeshAsset);
		_barrelMesh->SetupAttachment(GetStaticMeshComponent(), "BarrelAttachPoint");
		_barrelMesh->SetMobility(EComponentMobility::Movable);
	}

	_rotating = CreateDefaultSubobject<URotatingMovementComponent>("RotatingMovement");
	_rotating->RotationRate = FRotator(0.f, 0.f, 0.f);

	//Timeline設定
	_fireControlTimeline = new FTimeline();
	_fireControlTimeline->SetTimelineLength(4.f);
	static auto BarrelCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Script/Engine.CurveFloat'/Game/Curves/BarrelCurve.BarrelCurve'"));
	if (BarrelCurve)
	{
		FOnTimelineFloat BarrelTimelineStepFunc;
		BarrelTimelineStepFunc.BindUFunction(this, "BarrelTimelineStep");
		_fireControlTimeline->AddInterpFloat(BarrelCurve, BarrelTimelineStepFunc);
	}

	static auto BulletColorCurve = LoadObject<UCurveLinearColor>(NULL, TEXT("/Script/Engine.CurveLinearColor'/Game/Curves/BulletColorCurve.BulletColorCurve'"));
	if (BulletColorCurve)
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

	static auto BPBullet = LoadClass<AC_BulletBase>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/StaticMesh/BP_Bullet.BP_Bullet_c'"));
	BulletClass = BPBullet;

	static auto BPSensor = LoadClass<USceneComponent>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Components/BP_AC_Sensor.BP_AC_Sensor_c'"));
	if (BPSensor)
	{
		_sensor = Cast<UC_AC_SensorBase>(CreateDefaultSubobject("SensorComponent", BPSensor, BPSensor, true, false));
		_sensor->SetupAttachment(GetStaticMeshComponent(), "Muzzle");
	}
}

AC_TurretBase::~AC_TurretBase()
{
	delete _fireControlTimeline;
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
	auto checkData = _sensor->CheckSensor();
	//1番目要素はセンサーヒットの有無
	if (std::get<1>(checkData))
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
	float time = C_FuncLibrary::SafeDivide(1.f, (float)_fireRate);
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