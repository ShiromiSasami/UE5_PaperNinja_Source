// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/C_AC_SineCurveMovement.h"

#include "Libraries/C_FuncLibrary.h"

// Sets default values for this component's properties
UC_AC_SineCurveMovement::UC_AC_SineCurveMovement()
	:_amplitude(0, 0, 0),
	_period(1, 1, 1),
	_phase(0, 0, 0),
	_initialLocation(0, 0, 0)
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UC_AC_SineCurveMovement::BeginPlay()
{
	Super::BeginPlay();

	_initialLocation = GetOwner()->GetActorLocation();
	
}


// Called every frame
void UC_AC_SineCurveMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	double seconds = GetWorld()->GetTimeSeconds();

	float Xsin = C_FuncLibrary::SineCurve(seconds, _phase.X, _amplitude.X, _period.X);
	float Ysin = C_FuncLibrary::SineCurve(seconds, _phase.Y, _amplitude.Y, _period.Y);
	float Zsin = C_FuncLibrary::SineCurve(seconds, _phase.Z, _amplitude.Z, _period.Z);
	FVector nextLocation = _initialLocation + FVector(Xsin, Ysin, Zsin);

	GetOwner()->SetActorLocation(nextLocation);
}

