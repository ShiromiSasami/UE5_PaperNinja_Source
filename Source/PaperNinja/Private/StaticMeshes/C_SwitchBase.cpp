// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_SwitchBase.h"

#include "Libraries/C_FuncLibrary.h"

#include <Materials/MaterialInstanceConstant.h>
#include <Components/BoxComponent.h>
#include <GameFramework/Pawn.h>
#include <EngineUtils.h>

AC_SwitchBase::AC_SwitchBase()
	:bIsOn(false)
{
	const auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Kitbash/KSM_Switch.KSM_Switch"));
	const auto OnMatarialAsset = LoadObject<UMaterialInstanceConstant>(NULL, TEXT("/Game/Materials/MI_SwichOn.MI_SwichOn"));
	if (MeshAsset && OnMatarialAsset)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset);
		_mOff = MeshAsset->GetMaterial(0);
		_mOn = OnMatarialAsset;
	}
}

void AC_SwitchBase::BeginPlay()
{
	Super::BeginPlay();
}

void AC_SwitchBase::OnPawnOn_Implementation(AC_Pawn* pawn)
{
	bIsOn = !bIsOn;
	if (bIsOn)
	{
		if (_mOn)
		{
			GetStaticMeshComponent()->SetMaterial(0, _mOn);
		}
	}
	else
	{
		if (_mOff)
		{
			GetStaticMeshComponent()->SetMaterial(0, _mOff);
		}
	}

	OnChanged.Broadcast(this);
}

void AC_SwitchBase::OnPawnOff_Implementation(AC_Pawn* pawn)
{
}

