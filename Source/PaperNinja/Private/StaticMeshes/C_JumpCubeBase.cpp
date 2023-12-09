// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_JumpCubeBase.h"

#include "Characters/C_Pawn.h"
#include "Libraries/C_FuncLibrary.h"

#include <Materials/MaterialInstanceConstant.h>
#include <Components/StaticMeshComponent.h>
#include <Components/BoxComponent.h>
#include <EngineUtils.h>

AC_JumpCubeBase::AC_JumpCubeBase()
	:_destTransform(FVector(0.f, 0.f, 100.f)),
	bIsPlayingForward(false)
	
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponentÇÃèâä˙âª
	USceneComponent* DefaultRoot = GetRootComponent();
	if (!DefaultRoot)
	{
		DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
		RootComponent = DefaultRoot;
	}

	//StaticMeshComponentÇÃèâä˙âª
	static auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Props/SM_Framed_Box.SM_Framed_Box'"));
	static auto TriggerMatarialAsset = LoadObject<UMaterialInstanceConstant>(NULL, TEXT("/Script/Engine.MaterialInstanceConstant'/Game/Materials/MI_SwichOn.MI_SwichOn'"));
	_cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	if (MeshAsset && TriggerMatarialAsset)
	{
		_mOff = MeshAsset->GetMaterial(0);
		_mOn = TriggerMatarialAsset;
		_cube->SetStaticMesh(MeshAsset);
	}
	_cube->SetupAttachment(GetRootComponent());

	_liftTimeline = new FTimeline();
	_liftTimeline->SetTimelineLength(1.f);
	static auto JumpCubeFallCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Script/Engine.CurveFloat'/Game/Curves/JumpCubeLiftAlphaCurve.JumpCubeLiftAlphaCurve'"));
	if (JumpCubeFallCurve)
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

