// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/BP_FuncLibrary.h"

UBP_FuncLibrary::UBP_FuncLibrary()
{
}

FCalcRayStruct UBP_FuncLibrary::CalcRay(FVector origin, FVector direction, float length)
{
	FCalcRayStruct taple;
	taple.Start = origin;
	taple.End = C_FuncLibrary::CalcRay(taple.Start, direction, length);
	return taple;
}

bool UBP_FuncLibrary::IsPlayerPawn(AActor* actor)
{
	return C_FuncLibrary::IsPlayerPawn(actor);
}

void UBP_FuncLibrary::Cooldown(bool& IsCooldown, float Duration)
{
	C_FuncLibrary::Cooldown(IsCooldown, Duration);
}

float UBP_FuncLibrary::SineCurve(float time, float phase, float amplitude, float period)
{
	return C_FuncLibrary::SineCurve(time, phase, amplitude, period);
}
