// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/C_LSA_HellowWorld.h"

#include "PaperNinja/DebugTools.h"

void AC_LSA_HellowWorld::BeginPlay()
{
	Super::BeginPlay();
	Debug::Log("Hello,World");
}
