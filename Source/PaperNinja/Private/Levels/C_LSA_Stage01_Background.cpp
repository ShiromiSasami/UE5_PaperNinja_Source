// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/C_LSA_Stage01_Background.h"

#include <LevelSequenceActor.h>
#include <LevelSequencePlayer.h>

AC_LSA_Stage01_Background::AC_LSA_Stage01_Background()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AC_LSA_Stage01_Background::GoToNightTime_Implementation()
{
    if (_shellSequence)
    {
        _shellSequence->GetSequencePlayer()->Play();
    }
}
