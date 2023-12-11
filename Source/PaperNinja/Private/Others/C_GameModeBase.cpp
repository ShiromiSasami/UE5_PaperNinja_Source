// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_GameModeBase.h"

#include "Others/C_GameStateBase.h"

#include <Kismet/GameplayStatics.h>
#include <GameFramework/PlayerState.h>

AC_GameModeBase::AC_GameModeBase()
{
	if (const auto Pawn = LoadClass<APawn>(NULL, TEXT("/Game/Blueprints/Character/BP_Ninja.BP_Ninja_c")))
	{
		DefaultPawnClass = Pawn;
	}

	if (const auto ControllerClass = LoadClass<APlayerController>(NULL, TEXT("/Game/Blueprints/Other/BP_PlayerController.BP_PlayerController_c")))
	{
		PlayerControllerClass = ControllerClass;
		ReplaySpectatorPlayerControllerClass = ControllerClass;
	}

	if (const auto StateClass = LoadClass<APlayerState>(NULL, TEXT("/Game/Blueprints/Other/BP_PlayerState.BP_PlayerState_c")))
	{
		PlayerStateClass = StateClass;
	}

	if (const auto GameStateBaseClass = LoadClass<AGameStateBase>(NULL, TEXT("/Game/Blueprints/Other/BP_GameState.BP_GameState_c")))
	{
		GameStateClass = GameStateBaseClass;
	}
}

AActor* AC_GameModeBase::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (const auto stateBase = Cast<AC_GameStateBase>(UGameplayStatics::GetGameState(GetWorld())))
	{
		if (const auto checkpoint = stateBase->GetCheckpoint())
		{
			return checkpoint;
		}
	}
	
	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}
