// Fill out your copyright notice in the Description page of Project Settings.


#include "Materials/PM_Pushable.h"

UPM_Pushable::UPM_Pushable()
{
	Friction = 0.4f;
	FrictionCombineMode = EFrictionCombineMode::Min;
	bOverrideFrictionCombineMode = true;
	Density = 0.5f;

	SleepLinearVelocityThreshold = 0.f;
	SleepAngularVelocityThreshold = 0.f;
	SleepCounterThreshold = 0;
}
