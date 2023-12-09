// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "C_PlayerStateBase.generated.h"

/**
 * 
 */
UCLASS()
class PAPERNINJA_API AC_PlayerStateBase : public APlayerState
{
	GENERATED_BODY()
	
public:
	AC_PlayerStateBase();

	void SetCoinNum(const int num);
	int GetCoinNum() const;

protected:
	UPROPERTY(EditAnywhere, meta = (ToolTip = "é©ã@Ç™éÊÇ¡ÇΩÉRÉCÉìÇÃñáêî"))
	int _numOfCoins;

};
