// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_ScrollBase.h"

#include <Components/CapsuleComponent.h>
#include <GameFramework/Character.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <UObject/ConstructorHelpers.h>

AC_ScrollBase::AC_ScrollBase()
	:_aura(CreateDefaultSubobject<UStaticMeshComponent>("Aura"))
{
	const auto mesh = GetStaticMeshComponent();
	if (const auto MeshAsset = LoadObject<UStaticMesh>(NULL, TEXT("/Game/Props/SM_Scroll.SM_Scroll")))
	{
		mesh->SetStaticMesh(MeshAsset);
		mesh->SetCanEverAffectNavigation(false);
		mesh->SetRelativeRotation(FRotator(-40.f, 90.f, 0.f));
		mesh->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	}
	SetMobility(EComponentMobility::Movable);

	const auto trigger = CreateTrigger<UCapsuleComponent>("CapsuleCollision");
	trigger->SetCapsuleHalfHeight(18.f);
	trigger->SetCapsuleRadius(8.f);

	if (const auto SphereMesh = LoadObject<UStaticMesh>(NULL, TEXT("/Game/StarterContent/Props/MaterialSphere.MaterialSphere")))
	{
		_aura->SetStaticMesh(SphereMesh);
		_aura->SetCollisionProfileName("NoCollision");
		_aura->SetupAttachment(GetStaticMeshComponent());
	}
}

void AC_ScrollBase::BeginPlay()
{
	Super::BeginPlay();

	if (const auto AuraMaterial = TSoftObjectPtr<UMaterialInterface>(FSoftObjectPath("Game/Materials/M_Aura.M_Aura")).LoadSynchronous())
	{
		_aura->CreateDynamicMaterialInstance(0, AuraMaterial);
	}
}

bool AC_ScrollBase::CanBeObtained(APawn* pawn, APlayerController* playerController)
{
	bool obtained = Super::CanBeObtained(pawn, playerController);

	if (const ACharacter* character = Cast<ACharacter>(pawn))
	{
		const bool isFalling = character->GetCharacterMovement()->IsFalling();
		return (!isFalling && obtained);
	}

	return obtained;
}