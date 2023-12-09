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
 * ���v����C���^�[�t�F�[�X
 */
class PAPERNINJA_API IDayNightSystem
{
	GENERATED_BODY()

public:
	/// <summary>
	/// ���v����(�L�q�K�{)
	/// </summary>
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GoToNightTime();
	virtual void GoToNightTime_Implementation() = 0;

};
