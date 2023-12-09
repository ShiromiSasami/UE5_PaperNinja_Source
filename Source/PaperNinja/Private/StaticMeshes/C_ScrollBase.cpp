// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_ScrollBase.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <UObject/ConstructorHelpers.h>

AC_ScrollBase::AC_ScrollBase()
{
	static auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/Props/SM_Scroll.SM_Scroll'"));
	auto mesh = GetStaticMeshComponent();
	if (MeshAsset)
	{
		mesh->SetStaticMesh(MeshAsset);
		mesh->SetCanEverAffectNavigation(false);
		mesh->SetRelativeRotation(FRotator(-40.f, 90.f, 0.f));
		mesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	}
	SetMobility(EComponentMobility::Movable);

	auto trigger = CreateTrigger<UCapsuleComponent>("CapsuleCollision");
	trigger->SetCapsuleHalfHeight(18.f);
	trigger->SetCapsuleRadius(8.f);

	static auto SphereMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/MaterialSphere.MaterialSphere'"));
	if (SphereMesh)
	{
		_aura = CreateDefaultSubobject<UStaticMeshComponent>("Aura");
		_aura->SetStaticMesh(SphereMesh);
		_aura->SetCollisionProfileName("NoCollision");
		_aura->SetupAttachment(GetStaticMeshComponent());
	}
}

void AC_ScrollBase::BeginPlay()
{
	Super::BeginPlay();

	static auto AuraMaterial = LoadObject<UMaterialInterface>(NULL, TEXT("Game/Materials/M_Aura.M_Aura"));
	if (AuraMaterial)
	{
		_aura->CreateDynamicMaterialInstance(0, AuraMaterial);
	}
}

void AC_ScrollBase::ObtainedImpl(APawn* player, APlayerController* controller)
{
	Super::ObtainedImpl(player, controller);
	
}

bool AC_ScrollBase::CanBeObtained(APawn* pawn, APlayerController* playerController)
{
	bool obtained = Super::CanBeObtained(pawn, playerController);

	if (ACharacter* character = Cast<ACharacter>(pawn))
	{
		bool isFalling = character->GetCharacterMovement()->IsFalling();
		return (!isFalling && obtained);
	}

	return obtained;
}