// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_AN_SpawnSoundEmitter.h"

#include "Others/C_SoundEmitter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UC_AN_SpawnSoundEmitter::UC_AN_SpawnSoundEmitter()
{
}

void UC_AN_SpawnSoundEmitter::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (const auto pawn = Cast<ACharacter>( MeshComp->GetOwner()))
	{
		const auto velocity = pawn->GetVelocity();
		const float speed = FVector2D(velocity.X, velocity.Y).Length();
		if (speed >= 150.f || pawn->GetCharacterMovement()->IsFalling())
		{
			pawn->GetWorld()->SpawnActor<AC_SoundEmitter>(AC_SoundEmitter::StaticClass(), pawn->GetTransform());
		}
	}
}
