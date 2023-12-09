// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StaticMeshes/C_Pickup.h"
#include "C_ScrollBase.generated.h"

/**
 * 
 */
UCLASS()
class PAPERNINJA_API AC_ScrollBase : public AC_Pickup
{
	GENERATED_BODY()

public:
	AC_ScrollBase();

protected:
	virtual void BeginPlay() override;

	virtual void ObtainedImpl(APawn* player, APlayerController* controller) override;
	virtual bool CanBeObtained(APawn* pawn, APlayerController* playerController) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> _aura;
};
