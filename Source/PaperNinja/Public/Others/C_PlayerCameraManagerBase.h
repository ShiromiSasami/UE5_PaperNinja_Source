// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "C_PlayerCameraManagerBase.generated.h"

/**
 * プレイヤーカメラマネージャーの基底クラス
 */
UCLASS()
class PAPERNINJA_API AC_PlayerCameraManagerBase : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	AC_PlayerCameraManagerBase();

private:
	const FFloat16 VIEW_PITCH_MIN = -80.f;
	const FFloat16 VIEW_PITCH_MAX = -20.f;
};
