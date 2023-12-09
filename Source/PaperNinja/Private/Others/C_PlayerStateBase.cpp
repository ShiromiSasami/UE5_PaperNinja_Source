// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_PlayerStateBase.h"

AC_PlayerStateBase::AC_PlayerStateBase()
	:_numOfCoins(0)
{
}

void AC_PlayerStateBase::SetCoinNum(const int num)
{
	_numOfCoins = num;
}

int AC_PlayerStateBase::GetCoinNum() const
{
	return _numOfCoins;
}
