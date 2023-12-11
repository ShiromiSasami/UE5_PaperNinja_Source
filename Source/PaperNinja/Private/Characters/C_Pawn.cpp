// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_Pawn.h"

#include "Components/C_AC_SensorBase.h"

#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>
#include <Interfaces/Floor.h>
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputComponent.h>

AC_Pawn::AC_Pawn()
	:bIsSprinting(false)
{
	PrimaryActorTick.bCanEverTick = true;

	if (const auto ControllerClass = LoadClass<AController>(NULL, TEXT("/Game/AI/BP_AIController.BP_AIController_c")))
	{
		AIControllerClass = ControllerClass;
	}

	GetCharacterMovement()->bScalePushForceToVelocity = false;
	GetCharacterMovement()->PushForceFactor = 100000;
	GetMesh()->SetGenerateOverlapEvents(true);

	if (const auto BPSensor = LoadClass<UC_AC_SensorBase>(NULL, TEXT("/Game/Blueprints/Components/BP_AC_Sensor.BP_AC_Sensor_c")))
	{
		_sensor = Cast<UC_AC_SensorBase>(CreateDefaultSubobject("SensorComponent", BPSensor, BPSensor, true, false));
		_sensor->SetupAttachment(GetCapsuleComponent());
	}

	const auto movement = GetCharacterMovement();
	movement->MaxAcceleration = MAX_WALK_SPEED;
	movement->MaxWalkSpeed = MAX_WALK_SPEED;

	if (const auto AcceleCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Game/Curves/PawnAccelerationCurve.PawnAccelerationCurve")))
	{
		_acceleCurve = AcceleCurve;
	}

	if (const auto RotRateCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Game/Curves/PawnRotationRateCurve.PawnRotationRateCurve")))
	{
		_rotRateCurve = RotRateCurve;
	}
}

void AC_Pawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!_weaponMeshAsset) { return; }
	const auto weaponMesh = NewObject<UStaticMeshComponent>(this);
	_weaponMesh = Cast<UStaticMeshComponent>(weaponMesh);
	_weaponMesh->SetStaticMesh(_weaponMeshAsset);
	FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	_weaponMesh->AttachToComponent(GetMesh(), attachRules, "weapon_r");
}

void AC_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AC_Pawn::ComponentHit);
}

// Called every frame
void AC_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto currentFloor = GetCurrentFloor();
	if (currentFloor == _lastFloor) { return; }

	//“¥‚Ü‚È‚­‚È‚Á‚½‚±‚Æ‚ð’Ê’m
	auto floor = Cast<IFloor>(_lastFloor);
	if (floor)
	{
		floor->OnPawnOff_Implementation(this);
	}

	//“¥‚ñ‚¾‚±‚Æ‚ð’Ê’m
	floor = Cast<IFloor>(currentFloor);
	if (floor)
	{
		floor->OnPawnOn_Implementation(this);
	}
	_lastFloor = currentFloor;

	float yawRate = _rotRateCurve->GetFloatValue(GetCharacterMovement()->Velocity.Size());
	GetCharacterMovement()->RotationRate.Yaw = yawRate;

	float accele = _acceleCurve->GetFloatValue(GetCharacterMovement()->MaxWalkSpeed) ;
	GetCharacterMovement()->MaxAcceleration = accele;
}

void AC_Pawn::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::ApplyDamage(OtherActor, 1.f, nullptr, this, nullptr);
}

void AC_Pawn::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();

	OnPawnJumped.Broadcast(this);
}

bool AC_Pawn::BeginSprint()
{
	if (bIsSprinting) { return false; }
	GetCharacterMovement()->MaxWalkSpeed = MAX_SPRINT_SPEED;
	bIsSprinting = true;
	return true;
}

bool AC_Pawn::EndSprint()
{
	if (!bIsSprinting) { return false; }
	GetCharacterMovement()->MaxWalkSpeed = MAX_WALK_SPEED;
	bIsSprinting = false;
	return true;
}