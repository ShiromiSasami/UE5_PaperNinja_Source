// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Interfaces/DayNightSystem.h"
#include "C_LSA_Stage01_Background.generated.h"

/**
 * Backgroundサブレベルのレベルスクリプトアクター
 */
UCLASS()
class PAPERNINJA_API AC_LSA_Stage01_Background : public ALevelScriptActor, public IDayNightSystem
{
	GENERATED_BODY()
	
public:
	AC_LSA_Stage01_Background();

public:
	/// <summary>
	/// 日没処理
	/// </summary>
	virtual void GoToNightTime_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ALevelSequenceActor> _shellSequence;
};
