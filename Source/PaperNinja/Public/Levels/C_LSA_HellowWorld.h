// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "C_LSA_HellowWorld.generated.h"

/**
 * Helloworld���x���̃��x���X�N���v�g�A�N�^�[
 */
UCLASS()
class PAPERNINJA_API AC_LSA_HellowWorld : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	
};
