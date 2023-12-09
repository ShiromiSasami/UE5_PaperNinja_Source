// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UW_Title.generated.h"

enum class EButtonID : int16
{
	Start,
	Quit,
};

/**
 * TitleWidget‚ÌŠî‘bƒNƒ‰ƒX
 */
UCLASS()
class PAPERNINJA_API UC_UW_Title : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnClickedStart();
	UFUNCTION()
	void OnClickedQuit();

	UFUNCTION()
	void SelectMove(const FInputActionValue& value);
	UFUNCTION()
	void Select(const FInputActionValue& value);

	void UpdateUI();

protected:
	UPROPERTY(Transient, meta = (BindWidgetOptional))
	TObjectPtr<class UButton>  Start_Button;
	UPROPERTY(Transient, meta = (BindWidgetOptional))
	TObjectPtr<class UButton>  Quit_Button;

private:
	TObjectPtr<class UInputAction> _inputMove;
	TObjectPtr<class UInputAction> _inputSelect;
	TArray<EButtonID> _buttonID;
	int16 _currentIndex;
};
