// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Anim_RabbitBase.h"

#include "Characters/C_Pawn.h"

UAnim_RabbitBase::UAnim_RabbitBase()
	:bisSprint(false)
{
}

void UAnim_RabbitBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (const auto pOwner =  TryGetPawnOwner())
	{
		const auto velocity = pOwner->GetVelocity();
		_speed = FVector2D(velocity.X, velocity.Y).Length();

		if (auto pawn = Cast<AC_Pawn>(pOwner))
		{
			bisSprint = pawn->IsSprinting();
		}
	}
}
