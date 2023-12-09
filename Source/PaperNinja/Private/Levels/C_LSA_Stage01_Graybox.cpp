// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/C_LSA_Stage01_Graybox.h"

#include "Characters/C_RabbitBase.h"
#include "StaticMeshes/C_SwitchBase.h"
#include "StaticMeshes/C_GateBase.h"
#include "StaticMeshes/C_JumpCubeBase.h"
#include "StaticMeshes/C_CoinBase.h"
#include "StaticMeshes/C_ScrollBase.h"
#include "StaticMeshes/C_ChestBase.h"
#include "Others/C_GameStateBase.h"
#include "Levels/C_LSA_Stage01_Background.h"
#include "Components/C_AC_SineCurveMovement.h"
#include "Libraries/C_FuncLibrary.h"

#include <EngineUtils.h>
#include <Engine/TargetPoint.h>
#include <Engine/StaticMeshActor.h>
#include <Engine/TriggerBox.h>
#include <Engine/LevelStreaming.h>
#include <AIController.h>
#include <Kismet/GameplayStatics.h>
#include <Math/UnrealMathUtility.h>
#include <PhysicsEngine/PhysicsConstraintActor.h>
#include <PhysicsEngine/PhysicsConstraintComponent.h>
#include <PhysicsEngine/PhysicsThrusterComponent.h>
#include <Blueprint/UserWidget.h>

#include <LevelSequenceActor.h>
#include <LevelSequencePlayer.h>
#include <Blueprint/UserWidget.h>

AC_LSA_Stage01_Graybox::AC_LSA_Stage01_Graybox()
    : bIsPlayingForward(false),
    _floatBoxHitCount(0),
    bFloatBoxisHitting(false)
{
    PrimaryActorTick.bCanEverTick = true;

    _gearTimeline = new FTimeline();
    _gearTimeline->SetTimelineLength(5.f);

    auto* GearAlphaCurve = LoadObject<UCurveFloat>(NULL, TEXT("/Script/Engine.CurveFloat'/Game/Curves/GearAlphaCurve.GearAlphaCurve'"));
    if (GearAlphaCurve)
    {
        FOnTimelineFloat GearAlphaTimelineStepFunc;
        GearAlphaTimelineStepFunc.BindUFunction(this, "GearAlphaTimelineStep");
        _gearTimeline->AddInterpFloat(GearAlphaCurve, GearAlphaTimelineStepFunc);
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> ClearWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/GameClearWidget.GameClearWidget_c'"));
    if (ClearWidgetClass.Succeeded())
    {
        _clearWidgetClass = ClearWidgetClass.Class;
    }
}

AC_LSA_Stage01_Graybox::~AC_LSA_Stage01_Graybox()
{
    if (_gearTimeline)
    {
		delete _gearTimeline;
		_gearTimeline = nullptr;
	}
}

void AC_LSA_Stage01_Graybox::BeginPlay()
{
    Super::BeginPlay();

    if (_deathTrigger)
    {
        _deathTrigger->OnActorBeginOverlap.AddDynamic(this, &AC_LSA_Stage01_Graybox::OnTriggerOverlapBegin);
    }

    for (AC_SwitchBase* ns : _northSwiches)
    {
        ns->OnChanged.AddDynamic(this, &AC_LSA_Stage01_Graybox::OnNorthSwitchChanged);
    }

    for (AC_SwitchBase* cs : _craneSwiches)
    {
        cs->OnChanged.AddDynamic(this, &AC_LSA_Stage01_Graybox::OnCraneSwitchChanged);
    }

    if (_checkpointNE)
    {
        _checkpointNE->OnActorBeginOverlap.AddDynamic(this, &AC_LSA_Stage01_Graybox::SouthJumpCubeReset);
    }

    if (_checkpointSW)
    {
        _checkpointSW->OnActorBeginOverlap.AddDynamic(this, &AC_LSA_Stage01_Graybox::WestJumpCubeReset);
    }

    if (_floatBox)
    {
        _floatBox->OnActorHit.AddDynamic(this, &AC_LSA_Stage01_Graybox::OnFloatBoxHit);
    }

    if (_ironSphere)
    {
        _ironSphere->OnActorHit.AddDynamic(this, &AC_LSA_Stage01_Graybox::OnIronSphereHit);
    }

    if (_seesaw)
    {
        _seesaw->OnActorHit.AddDynamic(this, &AC_LSA_Stage01_Graybox::OnSeesawHit);
    }

    if (_floatChest)
    {
        _floatChest->OnObtained.BindLambda
        (
            [this](AActor* actor) {
                if (_chestBalloon)
                {
                    _chestBalloon->GetStaticMeshComponent()->SetSimulatePhysics(true);
                    if (auto thruster = _chestBalloon->GetComponentByClass(UPhysicsThrusterComponent::StaticClass()))
                    {
                        thruster->Activate(true);
                    }

                    if (auto sineCurve = _chestBalloon->GetComponentByClass(UC_AC_SineCurveMovement::StaticClass()))
                    {
                        sineCurve->SetComponentTickEnabled(false);
                    }
                }
            }
        );
    }

    auto state = Cast<AC_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
    if (state)
    {
        state->InitScrolls(_scrolls.Num());
    }
    for (int index = 0; index < _scrolls.Num(); ++index)
    {
        _scrolls[index]->OnObtained.BindLambda
            (
            [this, index, state](AActor* actor) {
                if (state)
                {
                    state->ObtainScroll(index);
                    if (state->HasCompletedLevel())
                    {
                        const FString ClearWidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/GameClearWidget.GameClearWidget_c'";
                        const TSubclassOf<UUserWidget> ClearWidgetClass = TSoftClassPtr<UUserWidget>(FSoftObjectPath(*ClearWidgetPath)).LoadSynchronous();
                        UUserWidget* clearWidget = CreateWidget<UUserWidget>(GetWorld(), ClearWidgetClass);
                        clearWidget->AddToViewport();
                        auto palyer = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
                        palyer->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
                        FTimerHandle timerHandle;
                        GetWorld()->GetTimerManager().SetTimer(timerHandle, [this]{ UGameplayStatics::OpenLevel(GetWorld(), "Title"); }, 5.f, false);
                    }
                }
            });
    }

    //_westJumpCubes[2]->SetDestination(FVector(100.f, 0.f, 0.f));
}

void AC_LSA_Stage01_Graybox::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_gearTimeline->IsPlaying() || _gearTimeline->IsReversing())
    {
        _gearTimeline->TickTimeline(DeltaTime);
    }

    if (auto* gameState = Cast<AC_GameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
    {
        if (gameState->HasCompletedLevel() && !_loadTitleLevel)
        {
            if (APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
            {
                if (ACharacter* character = Cast<ACharacter>(controller->GetPawn()))
                {
                    character->DisableInput(controller);
                    UUserWidget* clearWidget = CreateWidget<UUserWidget>(GetWorld(), _clearWidgetClass);
                    clearWidget->AddToViewport();

                    _loadTitleLevel = true;
                    FTimerHandle handle;
                    GetWorldTimerManager().SetTimer(handle, [WeakThis = TWeakObjectPtr<AActor>(this)]()
                        {
                            if (WeakThis.IsValid())
                            {
                                UGameplayStatics::OpenLevel(WeakThis->GetWorld(), "Title");
                            }
						}, 
                        5.f, false
                    );
                    
                }
            }
        }
    }
}

#pragma region BindFunction
void AC_LSA_Stage01_Graybox::OnTriggerOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    UGameplayStatics::ApplyDamage(OtherActor, 1.f, nullptr, OverlappedActor, nullptr);
}

void AC_LSA_Stage01_Graybox::GearAlphaTimelineStep(float value)
{
    auto location = FMath::Lerp(FVector(400.f, -400.f, 90.f), FVector(400.f, -400.f, 290.f), value);
    auto yaw = FMath::Lerp(0.f, -630.f, value);
    _gearTop->SetActorLocationAndRotation(location, FRotator(0, yaw, 0));
}

void AC_LSA_Stage01_Graybox::OnNorthSwitchChanged(AC_SwitchBase* switchActor)
{
    if (!_northGate || !_gearTimeline) { return; }
    for (AC_SwitchBase* sw : _northSwiches)
    {
        if (!sw->IsOn())
        {
            _northGate->Close();
            _gearTimeline->Reverse();
            return;
        }
    }

    _northGate->Open();
    _gearTimeline->Play();
    for (ATargetPoint* point : _bonusCoinPoints)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        auto coin = GetWorld()->SpawnActor<AC_CoinBase>(AC_CoinBase::StaticClass(), point->GetActorTransform(), SpawnParams);
        if (coin)
        {
            coin->EnableTossed();
            point->Destroy();
        }
    }
    _bonusCoinPoints.Empty();
}

void AC_LSA_Stage01_Graybox::OnCraneSwitchChanged(AC_SwitchBase* switchActor)
{
    if (!_craneSequence) { return; }
    if (switchActor->IsOn())
    {
        ++_switchCounter;
    }
    else
    {
        --_switchCounter;
    }

    FMovieSceneSequencePlayToParams playToParams;
    FMovieSceneSequencePlaybackParams playbackParams;
    playbackParams.MarkedFrame = FString::FromInt(_switchCounter);
    playbackParams.PositionType = EMovieScenePositionType::MarkedFrame;
    _craneSequence->GetSequencePlayer()->PlayTo(playbackParams, playToParams);
}

void AC_LSA_Stage01_Graybox::SouthJumpCubeReset(AActor* OverlappedActor, AActor* OtherActor)
{
    for (AC_JumpCubeBase* jumpCube : _southJumpCubes)
    {
        jumpCube->LiftReset();
    }

    auto gameState = Cast<AC_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
    gameState->SetCheckpoint(OverlappedActor);
}

void AC_LSA_Stage01_Graybox::WestJumpCubeReset(AActor* OverlappedActor, AActor* OtherActor)
{
    for (AC_JumpCubeBase* jumpCube : _westJumpCubes)
    {
        jumpCube->LiftReset();
    }

    auto gameState = Cast<AC_GameStateBase>(UGameplayStatics::GetGameState(GetWorld()));
    gameState->SetCheckpoint(OverlappedActor);

    if (!bIsPlayingForward)
    {
        bIsPlayingForward = true;
        auto bgStriming = UGameplayStatics::GetStreamingLevel(GetWorld(), "Stage01_Background");
        if (bgStriming && bgStriming->IsLevelLoaded())
        {
            auto bg = Cast<AC_LSA_Stage01_Background>(bgStriming->GetLoadedLevel()->GetLevelScriptActor());
            if (bg)
            {
                bg->GoToNightTime_Implementation();
            }
        }
    }
    
}

void AC_LSA_Stage01_Graybox::OnFloatBoxHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!C_FuncLibrary::IsPlayerPawn(OtherActor)) { return; }
    if (_floatBoxHitCount > 2 || bFloatBoxisHitting) { return; }
    ++_floatBoxHitCount;
    C_FuncLibrary::Cooldown(bFloatBoxisHitting, 0.25f);
    bFloatBoxisHitting = true;

    auto mesh = _floatBox->GetStaticMeshComponent();
    mesh->AddImpulse(FVector(0, -150.f, 150.f), NAME_None, true);
    mesh->AddAngularImpulseInDegrees(FVector(360, 0.f, 0.f), NAME_None, true);

    if (_floatBoxHitCount == 3 && _floatBalloonJoint)
    {
        _floatBalloonJoint->GetConstraintComp()->BreakConstraint();
        if (_boxBalloon)
        {
            _boxBalloon->GetStaticMeshComponent()->SetSimulatePhysics(true);
            if (auto thruster = _boxBalloon->GetComponentByClass(UPhysicsThrusterComponent::StaticClass()))
            {
                thruster->Activate(true);
            }

            if (auto sineCurve = _boxBalloon->GetComponentByClass(UC_AC_SineCurveMovement::StaticClass()))
            {
                sineCurve->SetComponentTickEnabled(false);
            }
        }
    }
}

void AC_LSA_Stage01_Graybox::OnIronSphereHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    UGameplayStatics::ApplyDamage(OtherActor, 1.f, nullptr, SelfActor, nullptr);
}

void AC_LSA_Stage01_Graybox::OnSeesawHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
    auto sMesh = _seesaw->GetStaticMeshComponent();
    sMesh->SetSimulatePhysics(true);
    if (_ironSphere)
    {
        auto iMesh = _ironSphere->GetStaticMeshComponent();
        iMesh->SetSimulatePhysics(true);
    }
}
#pragma endregion