// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_AC_SensorBase.h"

#include "Others/C_SoundEmitter.h"
#include "PaperNinja/DebugTools.h"

#include <GameFramework/Character.h>

// Sets default values for this component's properties
UC_AC_SensorBase::UC_AC_SensorBase()
	:_sightLength(800.f),
	_yawAngle(5.f),
	_pitchAngle(5.f)
{
	PrimaryComponentTick.bCanEverTick = false;

	_queryParams.AddIgnoredActor(GetOwner());
}

void UC_AC_SensorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

std::tuple<TArray<AActor*>, bool> UC_AC_SensorBase::CheckSensor()
{
	FTransform trans = GetComponentTransform();
	FVector start = trans.GetLocation();
	FVector dir = trans.GetRotation().GetForwardVector();
	FVector end = C_FuncLibrary::CalcRay(start, dir, _sightLength);
	float yawRad = FMath::DegreesToRadians(_yawAngle * 0.5f);
	float pitchRad = FMath::DegreesToRadians(_pitchAngle * 0.5f);
	float yawRange = tan(yawRad) * _sightLength;
	float pitchRange = tan(pitchRad) * _sightLength;
	FVector halfSize = FVector(1, yawRange, pitchRange);
	TArray<TEnumAsByte<EObjectTypeQuery> > types = { EObjectTypeQuery::ObjectTypeQuery3 };
	TArray<AActor*> ignoreedActors = { GetOwner() };
	TArray<AActor*> overlapActors;
	bool hit = C_FuncLibrary::SphereOverlapByChannel(GetWorld(), overlapActors, start, _sightLength, types, ACharacter::StaticClass(), ignoreedActors, _traceDebugParams);
	TArray<AActor*> actors;
	for (const auto& actor : overlapActors)
	{
		if (CanSeeActor(actor))
		{
			actors.Add(actor);
		}
	}

	return std::make_tuple(actors, !actors.IsEmpty());
}

bool UC_AC_SensorBase::CanSeeActor(AActor* tagetActor)
{
	if (!IsInSight(tagetActor->GetActorLocation())) { return false; }
	FHitResult lineResult;
	C_FuncLibrary::LineTraceByChannel(GetWorld(), lineResult, GetComponentLocation(), tagetActor->GetActorLocation(), ECollisionChannel::ECC_GameTraceChannel2, _traceDebugParams, _queryParams);
	if (lineResult.GetActor() == tagetActor)
	{
		return true;
	}
	if (_traceDebugParams.bEnable)
	{
		DrawDebugCone(GetWorld(), GetComponentLocation(), (tagetActor->GetActorLocation() - GetComponentLocation()).GetSafeNormal(), _sightLength, _yawAngle, _pitchAngle, 6, lineResult.bBlockingHit ? FColor::Red : FColor::Green, false, _traceDebugParams.LifeSpan);
	}
	return false;
}

bool UC_AC_SensorBase::DetectSound(TArray<FVector>& locations)
{
	TArray<TEnumAsByte<EObjectTypeQuery> > types = { EObjectTypeQuery::ObjectTypeQuery1 };
	TArray<AActor*> ignoreedActors = { GetOwner() };
	TArray<AActor*> overlapActors;
	bool hit = C_FuncLibrary::SphereOverlapByChannel(GetWorld(), overlapActors, GetComponentLocation(), _soundRadius, types, AC_SoundEmitter::StaticClass(), ignoreedActors, _traceDebugParams);
	if (hit)
	{
		for (auto actor : overlapActors)
		{
			locations.Add(actor->GetActorLocation());
		}
	}

	return hit;
}

bool UC_AC_SensorBase::IsInSight(FVector tagetLocation)
{
	FVector diffVecNormal = (tagetLocation - GetComponentLocation()).GetSafeNormal();
	FVector forwardVec = GetForwardVector();

	//ラジアンの垂直(Yaw)の角度
	double yawAngle = acos(forwardVec | diffVecNormal);
	if (yawAngle > FMath::DegreesToRadians(_yawAngle * 0.5)) {
		return false;
	}

	// 垂直方向の並行(Picth)角度
	double pitchAngle = acos(GetUpVector() | diffVecNormal);
	if (FMath::Abs(pitchAngle - (PI * 0.5)) > FMath::DegreesToRadians(_pitchAngle * 0.5)) {
		return false;
	}
	return true;
}


// Called every frame
void UC_AC_SensorBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

