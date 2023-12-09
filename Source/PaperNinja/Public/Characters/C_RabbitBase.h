// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/C_Pawn.h"
#include "C_RabbitBase.generated.h"

/**
 * ラビットの基礎クラス
 */
UCLASS()
class PAPERNINJA_API AC_RabbitBase : public AC_Pawn
{
	GENERATED_BODY()

public:
	AC_RabbitBase();

private:
	virtual void BeginPlay() override;

};
