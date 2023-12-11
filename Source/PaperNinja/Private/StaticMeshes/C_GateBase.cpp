// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_GateBase.h"

#include "Components/ArrowComponent.h"
#include "Curves/CurveVector.h"

AC_GateBase::AC_GateBase()
	: _arrow(CreateDefaultSubobject<UArrowComponent>("Arrow"))
	, _gateR(CreateDefaultSubobject<UStaticMeshComponent>("SM_Gate_R"))
	, _gateL(CreateDefaultSubobject<UStaticMeshComponent>("SM_Gate_L"))
	, _gateTimeline(new FTimeline())
{
	PrimaryActorTick.bCanEverTick = true;

	_arrow->ArrowColor = FColor::Cyan;
	RootComponent = _arrow;


	if (const auto GateRMeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Props/SM_Gate_R.SM_Gate_R")))
	{
		_gateR->SetStaticMesh(GateRMeshAsset);
		_gateR->SetRelativeLocation(FVector(0.f, 25.f, 0.f));
		_gateR->SetupAttachment(_arrow);
	}


	if (const auto GateLMeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Props/SM_Gate_L.SM_Gate_L")))
	{
		_gateL->SetStaticMesh(GateLMeshAsset);
		_gateL->SetRelativeLocation(FVector(0.f, -25.f, 0.f));
		_gateL->SetupAttachment(_arrow);
	}

	_gateTimeline->SetTimelineLength(2.5f);
	if (const auto GateMoveCurve = LoadObject<UCurveVector>(NULL, TEXT("/Game/Curves/GateMoveCurve.GateMoveCurve")))
	{
		FOnTimelineVector GateTimelineStepFunc;
		GateTimelineStepFunc.BindUFunction(this, "GateTimelineStep");
		_gateTimeline->AddInterpVector(GateMoveCurve, GateTimelineStepFunc);
	}
}

AC_GateBase::~AC_GateBase()
{
	if (_gateTimeline)
	{
		_gateTimeline->Stop();
		delete _gateTimeline;
		_gateTimeline = nullptr;
	}
}

void AC_GateBase::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void AC_GateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_gateTimeline->IsPlaying())
	{
		_gateTimeline->TickTimeline(DeltaTime);
	}

}

void AC_GateBase::GateTimelineStep(FVector vec)
{
	_gateR->SetRelativeLocation(vec);

	const auto lVec = vec * FVector(1.f, -1.f, 1.f);
	_gateL->SetRelativeLocation(lVec);
}

