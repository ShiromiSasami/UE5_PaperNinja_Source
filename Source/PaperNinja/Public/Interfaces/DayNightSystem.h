// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DayNightSystem.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UDayNightSystem : public UInterface
{
	GENERATED_BODY()
};

/**
 * 日没操作インターフェース
 */
class PAPERNINJA_API IDayNightSystem
{
	GENERATED_BODY()

public:
	/// <summary>
	/// 日没処理(記述必須)
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GoToNightTime();
	virtual void GoToNightTime_Implementation() = 0;

};
