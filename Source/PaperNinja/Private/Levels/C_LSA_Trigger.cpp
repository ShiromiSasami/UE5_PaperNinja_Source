// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/C_LSA_Trigger.h"

#include "PaperNinja/DebugTools.h"
#include "Characters/C_RabbitBase.h"
#include "StaticMeshes/C_JumpCubeBase.h"

#include <Kismet/GameplayStatics.h>
#include <Engine/StaticMeshActor.h>
#include <Engine/TriggerBox.h>
#include <EngineUtils.h>

AC_LSA_Trigger::AC_LSA_Trigger()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AC_LSA_Trigger::BeginPlay()
{
    Super::BeginPlay();

    if (_spikes)
    {
        _spikes->OnActorHit.AddDynamic(this, &AC_LSA_Trigger::OnSpikesHit);
    }

    if (_deathTrigger)
    {
        _deathTrigger->OnActorBeginOverlap.AddDynamic(this, &AC_LSA_Trigger::OnTriggerOverlapBegin);
    }

    if (_trampoline)
    {
        _trampoline->OnActorHit.AddDynamic(this, &AC_LSA_Trigger::OnTrampolineHit);
    }

    if (_enemy)
    {
        FTimerHandle handle;
        GetWorldTimerManager().SetTimer(
            handle, 
            [this] {
                _enemy->Jump();
                _enemy->BeginSprint();
            },
            5.0f,
            false
        );
    }

}

void AC_LSA_Trigger::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC && PC->WasInputKeyJustPressed(EKeys::R))
    {
        for (TActorIterator<AC_JumpCubeBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
        {
            if (const auto jumpCube = Cast<AC_JumpCubeBase>(*ActorItr)) { jumpCube->LiftReset(); }
        }
    }

    if (_enemy)
    {
        _enemy->AddMovementInput(FVector(0.f, 1.f, 0.f));
    }
}

void AC_LSA_Trigger::OnSpikesHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    UGameplayStatics::ApplyDamage(OtherActor, 1.f, nullptr, SelfActor, nullptr);
}

void AC_LSA_Trigger::OnTriggerOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    UGameplayStatics::ApplyDamage(OtherActor, 1.f, nullptr, OverlappedActor, nullptr);
}

void AC_LSA_Trigger::OnTrampolineHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    if (const auto character = Cast<ACharacter>(OtherActor))
    {
        character->Jump();
    }
}
