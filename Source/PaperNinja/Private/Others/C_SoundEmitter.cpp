// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_SoundEmitter.h"

#include <Components/SphereComponent.h>

// Sets default values
AC_SoundEmitter::AC_SoundEmitter()
{
	PrimaryActorTick.bCanEverTick = false;

	USphereComponent* CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->SetSphereRadius(1.f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetGenerateOverlapEvents(true);

	InitialLifeSpan = 0.1f;
}

