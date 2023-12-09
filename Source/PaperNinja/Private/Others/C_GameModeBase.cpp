// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_GameModeBase.h"

#include "Others/C_GameStateBase.h"

#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerState.h>

AC_GameModeBase::AC_GameModeBase()
{
	auto Pawn = LoadClass<APawn>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Character/BP_Ninja.BP_Ninja_c'"));
	if (Pawn)
	{
		DefaultPawnClass = Pawn;
	}

	auto ControllerClass = LoadClass<APlayerController>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Other/BP_PlayerController.BP_PlayerController_c'"));
	if (ControllerClass)
	{
		PlayerControllerClass = ControllerClass;
		ReplaySpectatorPlayerControllerClass = ControllerClass;
	}

	auto StateClass = LoadClass<APlayerState>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Other/BP_PlayerState.BP_PlayerState_c'"));
	if (StateClass)
	{
		PlayerStateClass = StateClass;
	}

	auto GameStateBaseClass = LoadClass<AGameStateBase>(NULL, TEXT("/Script/Engine.Blueprint'/Game/Blueprints/Other/BP_GameState.BP_GameState_c'"));
	if (GameStateBaseClass)
	{
		GameStateClass = GameStateBaseClass;
	}
}

AActor* AC_GameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (auto* stateBase = Cast<AC_GameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
	{
		if (auto* checkpoint = stateBase->GetCheckpoint())
		{
			return checkpoint;
		}
	}
	
	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}
