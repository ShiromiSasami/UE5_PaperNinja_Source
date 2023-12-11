// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_GameStateBase.h"

AC_GameStateBase::AC_GameStateBase()
{
}

void AC_GameStateBase::BeginPlay()
{
	Super::BeginPlay();
}

bool AC_GameStateBase::HasCompletedLevel() const
{
	if (_hasScrolls.IsEmpty()) return false;

	for (const bool hasScroll : _hasScrolls)
	{
		if (!hasScroll) return false;
	}

	return true;
}
