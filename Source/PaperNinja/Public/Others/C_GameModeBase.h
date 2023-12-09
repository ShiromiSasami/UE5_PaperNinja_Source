// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PAPERNINJA_API AC_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AC_GameModeBase();

public:
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName = "") override;
};
