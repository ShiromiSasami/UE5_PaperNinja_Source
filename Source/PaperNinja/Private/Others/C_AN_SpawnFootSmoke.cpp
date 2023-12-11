// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_AN_SpawnFootSmoke.h"

#include "GameFramework/Character.h"

#include <NiagaraFunctionLibrary.h>
#include <NiagaraSystem.h>
#include <Components/SkeletalMeshComponent.h>
#include <EngineUtils.h>

UC_AN_SpawnFootSmoke::UC_AN_SpawnFootSmoke()
{
	//NiagaraSystem�̓ǂݍ���
	if (const auto FX = LoadObject<UNiagaraSystem>(NULL, TEXT("/Game/Particles/Niagara/FXS_FootSmoke.FXS_FootSmoke")))
	{
		_spawnNiagara = FX;
	}
}

void UC_AN_SpawnFootSmoke::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (const auto pawn = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		const auto velocity = pawn->GetVelocity();
		const float speed = FVector2D(velocity.X, velocity.Y).Length();
		if (speed >= 150.f )
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(pawn->GetWorld(), _spawnNiagara, pawn->GetMesh()->GetSocketLocation(_soketName));
		}
	}
}
