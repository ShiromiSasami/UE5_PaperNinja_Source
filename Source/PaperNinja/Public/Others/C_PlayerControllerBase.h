// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PAPERNINJA_API AC_PlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	AC_PlayerControllerBase();
	
private:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn) override;

	void SetupInput();
	void JumpAction(const struct FInputActionValue& value);

	UFUNCTION()
	void OnPawnEndPlay(AActor* actor, EEndPlayReason::Type endPlayReason);

private:
	//ì¸óÕópÉÅÉìÉo
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInputMappingContext> _imc;
	UPROPERTY(EditAnywhere)
	TObjectPtr <class UInputAction> _inputJump;
};
