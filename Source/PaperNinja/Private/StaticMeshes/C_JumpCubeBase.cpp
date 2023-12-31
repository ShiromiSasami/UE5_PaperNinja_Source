// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_JumpCubeBase.h"

#include "Characters/C_Pawn.h"
#include "Libraries/C_FuncLibrary.h"

#include <Materials/MaterialInstanceConstant.h>
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include <EngineUtils.h>

AC_JumpCubeBase::AC_JumpCubeBase()
	:_cube(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh")))
	, _liftTimeline(new FTimeline())
	, _destTransform(FVector(0.f, 0.f, 100.f))
	, bIsPlayingForward(false)
	
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponentの初期化
	USceneComponent* DefaultRoot = GetRootComponent();
	if (!DefaultRoot)
	{
		DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
		RootComponent = DefaultRoot;
	}

	//StaticMeshComponentの初期化
	const auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Props/SM_Framed_Box.SM_Framed_Box"));
	const auto TriggerMatarialAsset = LoadObject<UMaterialInstanceConstant>(NULL, TEXT("/Game/Materials/MI_SwichOn.MI_SwichOn"));
	if (MeshAsset && TriggerMatarialAsset)
	{
		_mOff = MeshAsset->GetMaterial(0);
		_mOn = TriggerMatarialAsset;
		_cube->SetStaticMesh(MeshAsset);
	}
	_cube->SetupAttachment(GetRootComponent());

	_liftTimeline->SetTimelineLength(1.f);
	if (const auto JumpCubeFallCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Game/Curves/JumpCubeLiftAlphaCurve.JumpCubeLiftAlphaCurve")))
	{
		FOnTimelineFloat JumpCubeFallTimelineStepFunc;
		JumpCubeFallTimelineStepFunc.BindUFunction(this, "JumpCubeLiftTimelineStep");
		_liftTimeline->AddInterpFloat(JumpCubeFallCurve, JumpCubeFallTimelineStepFunc);
	}
}

AC_JumpCubeBase::~AC_JumpCubeBase()
{
	if (_liftTimeline)
	{
		_liftTimeline->Stop();
		delete _liftTimeline;
		_liftTimeline = nullptr;
	}
}

// Called when the game starts or when spawned
void AC_JumpCubeBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AC_JumpCubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_liftTimeline->IsPlaying() || _liftTimeline->IsReversing())
	{
		_liftTimeline->TickTimeline(DeltaTime);
	}

}

void AC_JumpCubeBase::JumpCubeLiftTimelineStep(float value)
{
	FVector lerpLocation = FMath::Lerp(_identity.GetLocation(), _destTransform.GetLocation(), value);
	FQuat lerpQuat = FMath::Lerp(_identity.GetRotation(), _destTransform.GetRotation(), value);
	FVector lerpScale = FMath::Lerp(_identity.GetScale3D(), _destTransform.GetScale3D(), value);
	const FTransform nextTrans = _dummyCube.Inverse() * FTransform(lerpQuat, lerpLocation, lerpScale) * GetActorTransform();
	SetActorTransform(nextTrans);
	_dummyCube = FTransform(lerpQuat, lerpLocation, lerpScale);
}

void AC_JumpCubeBase::Toggle(AC_Pawn* actor)
{
	bIsPlayingForward = !bIsPlayingForward;
	if (bIsPlayingForward)
	{
		_liftTimeline->Play();
	}
	else
	{
		_liftTimeline->Reverse();
	}

	actor->OnPawnJumped.RemoveDynamic(this, &AC_JumpCubeBase::Toggle);
}

void AC_JumpCubeBase::OnPawnOn_Implementation(AC_Pawn* pawn)
{
	if (_mOn)
	{
		_cube->SetMaterial(0, _mOn);
	}

	pawn->OnPawnJumped.AddDynamic(this, &AC_JumpCubeBase::Toggle);
}

void AC_JumpCubeBase::OnPawnOff_Implementation(AC_Pawn* pawn)
{
	if (_mOff)
	{
		_cube->SetMaterial(0, _mOff);
	}

	pawn->OnPawnJumped.RemoveDynamic(this, &AC_JumpCubeBase::Toggle);
}

