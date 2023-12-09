// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "C_LSA_Title.generated.h"

/**
 * タイトルレベルのレベルスクリプト
 */
UCLASS()
class PAPERNINJA_API AC_LSA_Title : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	AC_LSA_Title();

protected:
	virtual void BeginPlay() override;
};
