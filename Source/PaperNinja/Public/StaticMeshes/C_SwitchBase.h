// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Floor.h"
#include <Engine/StaticMeshActor.h>
#include "C_SwitchBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FChangedSignature, AC_SwitchBase, OnChanged, AC_SwitchBase*, switchActor );

/**
 * 
 */
UCLASS()
class PAPERNINJA_API AC_SwitchBase : public AStaticMeshActor, public IFloor
{
	GENERATED_BODY()

public:
	AC_SwitchBase();

private:
	virtual void BeginPlay() override;
	virtual void OnPawnOn_Implementation(AC_Pawn* pawn) override;
	virtual void OnPawnOff_Implementation(AC_Pawn* pawn) override;

public:
	FChangedSignature OnChanged;
	FORCEINLINE bool IsOn() const { return bIsOn; };

protected:
	TObjectPtr<class UMaterialInterface> _mOn;
	TObjectPtr<class UMaterialInterface> _mOff;

	bool bIsOn;
};
