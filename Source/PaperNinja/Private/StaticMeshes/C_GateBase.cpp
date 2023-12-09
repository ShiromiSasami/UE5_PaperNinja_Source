// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_GateBase.h"

#include "Components/ArrowComponent.h"
#include "Curves/CurveVector.h"

AC_GateBase::AC_GateBase()
{
	PrimaryActorTick.bCanEverTick = true;

	_arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	_arrow->ArrowColor = FColor::Cyan;
	RootComponent = _arrow;


	static auto GateRMeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Props/SM_Gate_R.SM_Gate_R'"));
	if (GateRMeshAsset)
	{
		_gateR = CreateDefaultSubobject<UStaticMeshComponent>("SM_Gate_R");
		_gateR->SetStaticMesh(GateRMeshAsset);
		_gateR->SetRelativeLocation(FVector(0.f, 25.f, 0.f));
		_gateR->SetupAttachment(_arrow);
	}


	static auto GateLMeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Props/SM_Gate_L.SM_Gate_L'"));
	if (GateLMeshAsset)
	{
		_gateL = CreateDefaultSubobject<UStaticMeshComponent>("SM_Gate_L");
		_gateL->SetStaticMesh(GateLMeshAsset);
		_gateL->SetRelativeLocation(FVector(0.f, -25.f, 0.f));
		_gateL->SetupAttachment(_arrow);
	}

	_gateTimeline = new FTimeline();
	_gateTimeline->SetTimelineLength(2.5f);
	const auto GateMoveCurve = LoadObject<UCurveVector>(NULL, TEXT("/Script/Engine.CurveVector'/Game/Curves/GateMoveCurve.GateMoveCurve'"));
	if (GateMoveCurve)
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
	if (_gateR)
	{
		_gateR->SetRelativeLocation(vec);
	}

	if (_gateL)
	{
		auto lVec = vec * FVector(1.f, -1.f, 1.f);
		_gateL->SetRelativeLocation(lVec);
	}
}

