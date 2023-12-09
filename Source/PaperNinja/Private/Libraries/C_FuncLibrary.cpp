#include "C_FuncLibrary.h"

#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/Playercontroller.h>

using namespace UE::Tasks;

C_FuncLibrary::C_FuncLibrary()
{
}

FVector C_FuncLibrary::CalcRay(FVector start, FVector direction, float length)
{
	return start + (direction * length);
}

bool C_FuncLibrary::IsPlayerPawn(AActor* actor)
{
	if (auto pawn = Cast<APawn>(actor))
	{
		if (auto player = Cast<APlayerController>(pawn->GetController()))
		{
			return true;
		}
	}
	return false;
}

float C_FuncLibrary::SafeDivide(float num, float den)
{
	
	if (FMath::IsNearlyZero(den))
	{
		return 0;
	}
	return num / den;
}

void C_FuncLibrary::Cooldown(bool& IsCooldown, float Duration)
{
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [&IsCooldown, Duration]()
	{
		float StartTime = FPlatformTime::Seconds();
		do
		{
			if (Duration <= FPlatformTime::Seconds() - StartTime)
			{
				IsCooldown = false;
			}

		} while (IsCooldown);
	});
}

float C_FuncLibrary::SineCurve(float time, float phase, float amplitude, float period)
{
	//1•b‚ ‚½‚è‚Ì‰ñ“]‘¬“x(1ŽüŠú‚É‚©‚©‚éŽžŠÔ)
	float angularVelocityPerSecond = SafeDivide(2 * PI, period);

	//A * Sin((w * t) + theta)
	return amplitude * sin((angularVelocityPerSecond * time) + phase);
}

bool C_FuncLibrary::LineTraceByChannel(
	UWorld* world, 
	FHitResult& result,
	const FVector start, 
	const FVector end,
	ECollisionChannel traceChannel,
	FTraceDebugParams& debugParams,
	const FCollisionQueryParams& params, 
	const FCollisionResponseParams& responseParams)
{
	bool bHit = world->LineTraceSingleByChannel(result, start, end, traceChannel, params, responseParams);
	if (debugParams.bEnable)
	{
		DrawDebugLine(world, start, end, bHit ? FColor::Red : FColor::Green, false, debugParams.LifeSpan);
		if (result.bBlockingHit)
		{
			DrawDebugPoint(world, result.Location, 10.f, FColor::Red,false, debugParams.LifeSpan);
		}
	}

	return bHit;
}

bool C_FuncLibrary::MultiBoxTraceByChannel(
	UWorld* world,
	TArray<FHitResult>& results,
	const FVector start,
	const FVector end,
	const FVector halfSize,
	const FQuat quat,
	ECollisionChannel traceChannel,
	FTraceDebugParams& debugParams,
	const FCollisionQueryParams& params,
	const FCollisionResponseParams& responseParams)
{
	bool bHit = world->SweepMultiByChannel(results, start, end, quat, traceChannel, FCollisionShape::MakeBox(halfSize), params, responseParams);
	if (debugParams.bEnable)
	{
		FVector drowSize = halfSize;
		drowSize.X = (end - start).Length() / 2;
		DrawDebugBox(world, start + (end - start) / 2, drowSize, quat, bHit ? FColor::Red : FColor::Green, false, debugParams.LifeSpan);
		for (int i = 0; i < results.Num(); ++i)
		{
			DrawDebugPoint(world, results[i].Location, 10.f, FColor::Red, false, debugParams.LifeSpan);
		}
	}

	return bHit;
}

bool C_FuncLibrary::LineTraceByProfile(
	UWorld* world,
	FHitResult& result,
	const FVector start,
	const FVector end,
	const FName profileName,
	FTraceDebugParams& debugParams,
	const FCollisionQueryParams& params)
{
	bool bHit = world->LineTraceSingleByProfile(result, start, end, profileName,  params);
	if (debugParams.bEnable)
	{
		DrawDebugLine(world, start, end, bHit ? FColor::Red : FColor::Green, false, debugParams.LifeSpan);
		if (result.bBlockingHit)
		{
			DrawDebugPoint(world, result.Location, 10.f, FColor::Red, false, debugParams.LifeSpan);
		}
	}
	return bHit;
}

bool C_FuncLibrary::SphereOverlapByChannel(
	UWorld* world, 
	TArray<AActor*>& outActors,
	const FVector start,
	const float radius, 
	const TArray<TEnumAsByte<EObjectTypeQuery> >& objectTypes,
	UClass* actorClassFilter,
	const TArray<AActor*>& actorsToIgnore,
	FTraceDebugParams& debugParams)
{
	bool bHit = UKismetSystemLibrary::SphereOverlapActors(world, start, radius, objectTypes,actorClassFilter, actorsToIgnore, outActors);
	if (debugParams.bEnable)
	{
		DrawDebugSphere(world, start, radius, 64, bHit ? FColor::Red : FColor::Green, false, debugParams.LifeSpan);
	}
	return bHit;
}