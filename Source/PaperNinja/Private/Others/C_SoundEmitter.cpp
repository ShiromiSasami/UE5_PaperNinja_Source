// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_SoundEmitter.h"

#include <Components/SphereComponent.h>

// Sets default values
AC_SoundEmitter::AC_SoundEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	USphereComponent* CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	CollisionComponent->SetSphereRadius(1.f);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = CollisionComponent;
	CollisionComponent->SetGenerateOverlapEvents(true);

	InitialLifeSpan = 0.1f;
}

// Called when the game starts or when spawned
void AC_SoundEmitter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_SoundEmitter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

