// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Anim_NinjaBase.h"

#include "Others/C_GameStateBase.h"

#include <GameFramework/PawnMovementComponent.h>

UAnim_NinjaBase::UAnim_NinjaBase()
	:bHasCompletedLevel(false),
	bIsInAir(false),
	bCanJump(true)
{
}

void UAnim_NinjaBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (const auto pOwner = TryGetPawnOwner())
	{
		auto velocity = pOwner->GetVelocity();
		_speed = FVector2D(velocity.X, velocity.Y).Length();

		bIsInAir = pOwner->GetMovementComponent()->IsFalling();
	}

	if (const auto state = Cast<AC_GameStateBase>(GetWorld()->GetGameState()))
	{
		bHasCompletedLevel = state->HasCompletedLevel();
	}

	if ("OnGround" == GetCurrentStateName(0))
	{
		bCanJump = true;
	}
	else
	{
		bCanJump = false;
	}
}
