// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/C_NinjaBase.h"

#include "PaperNinja/DebugTools.h"

#include <Components/SkeletalMeshComponent.h>
#include <Components/CapsuleComponent.h>
#include <Components/ArrowComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <Animation/AnimBlueprint.h>
#include <NiagaraFunctionLibrary.h>
#include <NiagaraSystem.h>

// Sets default values
AC_NinjaBase::AC_NinjaBase()
	:_springArm(CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"))),
	_camera(CreateDefaultSubobject<UCameraComponent>(TEXT("camera"))),
	bDead(false)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = false;

	//SkeletalMeshComponentの初期化
	if (const auto MeshAsset = LoadObject<USkeletalMesh>(NULL, TEXT("/Game/Characters/SK_Ninja.SK_Ninja")))
	{
		auto mesh = GetMesh();
		mesh->SetSkeletalMeshAsset(MeshAsset);
		mesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -44.f), FRotator(0.f, -90.f, 0.f));

		//アニメーションの設定
		if (const auto ABPAsset = LoadClass<UAnimInstance>(NULL, TEXT("/Game/Animations/ABP_Ninja.ABP_Ninja_c")))
		{
			mesh->AnimClass = ABPAsset;
		}
	}

	//CapsuleComponentの初期化
	const auto capsule = GetCapsuleComponent();
	capsule->SetCapsuleHalfHeight(44.f);

	//CameraSystemの初期化
	_springArm->bDoCollisionTest = false;
	_springArm->TargetArmLength = ARM_LENGTH;
	_springArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 40.f), FRotator(-40.f, 0.f, 0.f));
	_springArm->bUsePawnControlRotation = true;
	_springArm->SetupAttachment(capsule);
	_springArm->bDoCollisionTest = true;

	_camera->FieldOfView = FOV;
	_camera->SetupAttachment(_springArm);

	//NiagaraSystemの読み込み
	if (const auto FX = LoadObject<UNiagaraSystem>(NULL, TEXT("/Game/Particles/Niagara/FXS_Death.FXS_Death")))
	{
		_fxTemplate = FX;
	}

	//MovementComponentの初期化
	const auto movement = GetCharacterMovement();
	movement->MaxStepHeight = MAX_STEP_HEIGHT;
	movement->RotationRate.Roll = ROTATION_RATE_ROLL;
	movement->JumpZVelocity = JUMP_Z_VELOCITY;
	movement->AirControl = AIR_CONTROL;
	movement->PerchRadiusThreshold = PERCH_RADIUS_THRESHOLD;
	movement->PerchAdditionalHeight = PERCH_ADDITIONAL_HEIGHT;
	movement->bOrientRotationToMovement = true;

	_inputForceKill = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_ForceKill.IA_ForceKill"));
	_inputLook = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Look.IA_Look"));
	_inputMove = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Move.IA_Move"));
	_inputSprint = LoadObject<UInputAction>(NULL, TEXT("/Game/Inputs/IA_Sprint.IA_Sprint"));
}

// Called when the game starts or when spawned
void AC_NinjaBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_NinjaBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*auto velocity = GetVelocity();
	velocity.Z = 0.f;
	auto length = velocity.Length();
	Debug::Log(FString::SanitizeFloat(length), FColor::Cyan, 1);

	FVector start = GetActorLocation();
	FVector end = start + velocity;
	DrawDebugLine(GetWorld(), start, end, FColor::Cyan, false, 0.f, 0, 2.0f);*/
}

// Called to bind functionality to input
void AC_NinjaBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const auto eic = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		eic->BindAction(_inputForceKill, ETriggerEvent::Triggered, this, &AC_NinjaBase::ForceKillAction);
		eic->BindAction(_inputLook, ETriggerEvent::Triggered, this, &AC_NinjaBase::LookAction);
		eic->BindAction(_inputMove, ETriggerEvent::Triggered, this, &AC_NinjaBase::MoveAction);
		eic->BindAction(_inputSprint, ETriggerEvent::Triggered, this, &AC_NinjaBase::SprintAction);
		eic->BindAction(_inputSprint, ETriggerEvent::Completed, this, &AC_NinjaBase::SprintAction);
	}
}

float AC_NinjaBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bDead) { return ActualDamage; }

	bDead = true;

	if (const auto movement = GetCharacterMovement())
	{
		movement->DisableMovement();
	}
	SetLifeSpan(LifeSpanCount);
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->AddImpulseToAllBodiesBelow(FVector(0, 0, 600), NAME_None, true);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Spectator"));

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), _fxTemplate, GetActorLocation());

	return ActualDamage;
}

void AC_NinjaBase::ForceKillAction(const FInputActionValue& value)
{
	UGameplayStatics::ApplyDamage(this, 1.f, GetController(), this, nullptr);
}

void AC_NinjaBase::LookAction(const FInputActionValue& value)
{
	FVector2D vec = value.Get<FVector2D>();
	AddControllerYawInput(vec.X);
	AddControllerPitchInput(vec.Y);
}

void AC_NinjaBase::MoveAction(const FInputActionValue& value)
{
	FVector fVec = _camera->GetRightVector().Cross(GetActorUpVector());

	FVector2D vec = value.Get<FVector2D>();
	AddMovementInput(fVec, vec.Y);
	AddMovementInput(_camera->GetRightVector(), vec.X);
}

void AC_NinjaBase::SprintAction(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		BeginSprint();
	}
	else
	{
		EndSprint();
	}
}

