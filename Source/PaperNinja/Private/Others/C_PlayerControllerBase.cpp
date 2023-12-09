// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_PlayerControllerBase.h"

#include "Characters/C_NinjaBase.h"
#include "Others/C_GameModeBase.h"
#include "PaperNinja/DebugTools.h"

#include <InputMappingContext.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>

#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/GameModeBase.h>
#include <Kismet/GameplayStatics.h>
#include <UObject/ConstructorHelpers.h>
#include <Engine/LocalPlayer.h>
#include <Animation/AnimInstance.h>
#include <Animation/AnimStateMachineTypes.h>

AC_PlayerControllerBase::AC_PlayerControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	auto CameraManagerClass = LoadClass<APlayerCameraManager>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Other/BP_PlayerCameraManager.BP_PlayerCameraManager_c'"));
	if (CameraManagerClass)
	{
		PlayerCameraManagerClass = CameraManagerClass;
	}

	_inputJump = LoadObject<UInputAction>(NULL, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Jump.IA_Jump'"), NULL, LOAD_None, NULL);
	_imc = LoadObject<UInputMappingContext>(NULL, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Default.IMC_Default'"), NULL, LOAD_None, NULL);
}

void AC_PlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	SetupInput();
}

void AC_PlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	aPawn->OnEndPlay.AddDynamic(this, &AC_PlayerControllerBase::OnPawnEndPlay);
}

void AC_PlayerControllerBase::SetupInput()
{
	EnableInput(this);

	if (!InputComponent) return;
	if (auto eic = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		eic->BindAction(_inputJump, ETriggerEvent::Triggered, this, &AC_PlayerControllerBase::JumpAction);
	}

	if (auto controller = CastChecked<APlayerController>(this))
	{
		if (auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(_imc, 0);
		}
	}
}

void AC_PlayerControllerBase::JumpAction(const FInputActionValue& value)
{
	auto* player = GetCharacter();
	if (player && player->CanJump())
	{
		FVector velocity = player->GetVelocity();
		velocity.Z = 0.f;
		float length = velocity.Length();
		if (length >= 10.f)
		{
			player->Jump();
		}
		else
		{
			player->GetMesh()->GetAnimInstance()->RequestTransitionEvent("StartJump", 0.1, ETransitionRequestQueueMode::Shared, ETransitionRequestOverwriteMode::Append);

			FTimerHandle handle;
			GetWorldTimerManager().SetTimer(
				handle,
				[this] {
					GetCharacter()->Jump();
				},
				0.3f, false
			);
		}
	}
}

void AC_PlayerControllerBase::OnPawnEndPlay(AActor* actor, EEndPlayReason::Type endPlayReason)
{
	switch (endPlayReason)
	{
		case EEndPlayReason::Destroyed:
			if (auto* gameMode = UGameplayStatics::GetGameMode(GetWorld()))
			{
				gameMode->RestartPlayer(this);
			}
			break;
		case EEndPlayReason::LevelTransition:
			break;
		case EEndPlayReason::EndPlayInEditor:
			break;
		case EEndPlayReason::RemovedFromWorld:
			break;
		case EEndPlayReason::Quit:
			break;
		default:
			break;
	}
}
