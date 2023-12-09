// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/C_LSA_Event.h"

#include "Libraries/C_FuncLibrary.h"
#include "StaticMeshes/C_GateBase.h"
#include "StaticMeshes/C_CoinBase.h"
#include "StaticMeshes/C_SwitchBase.h"

#include <Engine/TargetPoint.h>

AC_LSA_Event::AC_LSA_Event()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AC_LSA_Event::BeginPlay()
{
    Super::BeginPlay();

    for (AC_CoinBase* coin : _gate1Coins)
    {
        coin->OnObtained.BindUFunction(this, FName("OnGate1CoinObtained"));
    }
    for (AC_SwitchBase* sw : _gate2Switches)
    {
        sw->OnChanged.AddDynamic(this, &AC_LSA_Event::OnSwitchChanged);
    }
}

void AC_LSA_Event::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        if (!_gate0) { return; }
        if (PC->WasInputKeyJustPressed(EKeys::O))
        {
            _gate0->Open();
        }
        if (PC->WasInputKeyJustReleased(EKeys::O))
        {
            _gate0->Close();
        }
    }
}

void AC_LSA_Event::OnGate1CoinObtained(AC_CoinBase* coin)
{
    _gate1Coins.RemoveAll([&coin](const TObjectPtr<AC_CoinBase>& element) { return (element == coin); });

    if (_gate1Coins.IsEmpty())
    {
        C_FuncLibrary::ForEachLoopWithDelay(_bonusCoinPoints, 2.0, this, "SpawnCoinLoopBody", "SpawnCoinCompleted");
    }
}

void AC_LSA_Event::OnSwitchChanged(AC_SwitchBase* switchActor)
{
    for (AC_SwitchBase* sw : _gate2Switches)
    {
        if (!sw->IsOn()) { return; }
    }

    if (!_gate2) { return; }
    _gate2->Open();
}

void AC_LSA_Event::OnBonusCoinObtained(AC_CoinBase* coin)
{
    _spawnedCoins.RemoveAll([&coin](const TObjectPtr<AC_CoinBase>& element) { return (element == coin); });
    if (!_gate1 || !_spawnedCoins.IsEmpty()) { return; }
    _gate1->Open();
}

void AC_LSA_Event::SpawnCoinLoopBody(int index)
{
    int idx = index;
    AC_CoinBase* coin = GetWorld()->SpawnActor<AC_CoinBase>(AC_CoinBase::StaticClass(), _bonusCoinPoints[idx]->GetActorTransform());
    coin->EnableTossed();
    coin->OnObtained.BindUFunction(this, FName("OnBonusCoinObtained"));
    _spawnedCoins.Add(coin);
    _bonusCoinPoints[idx]->Destroy();
}

void AC_LSA_Event::SpawnCoinCompleted(int index)
{
    _bonusCoinPoints.Empty();
}
