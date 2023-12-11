// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticMeshes/C_Pickup.h"

#include "PaperNinja/DebugTools.h"

#include <Components/SphereComponent.h>
#include <GameFramework/Pawn.h>

AC_Pickup::AC_Pickup()
{
}

void AC_Pickup::BeginPlay()
{
	Super::BeginPlay();

	_trigger->OnComponentBeginOverlap.AddDynamic(this, &AC_Pickup::ComponentBeginOverlap);
}

void AC_Pickup::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto pawn = Cast<APawn>(OtherActor))
	{
		if (const auto playerController = Cast<APlayerController>(pawn->GetController()))
		{
			if (CanBeObtained(pawn, playerController))
			{
				ObtainedImpl(pawn, playerController);
				OnObtained.ExecuteIfBound(this);
				Destroy();
			}
		}
	}
}

bool AC_Pickup::CanBeObtained(APawn* pawn, APlayerController* playerController)
{
	//‹–—e‚Å0.00001ˆÈ‰º‚ÌLifeSpan‚Í0‚Æ‚·‚é
	return (pawn->GetLifeSpan() <= 0.00001);
}