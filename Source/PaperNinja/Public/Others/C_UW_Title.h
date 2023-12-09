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
 * TitleWidgetの基礎クラス
 */
UCLASS()
class PAPERNINJA_API UC_UW_Title : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;

protected:
	/// <summary>
	/// Startボタンが押された時の処理
	/// </summary>
	UFUNCTION()
	void OnClickedStart();

	/// <summary>
	/// Quitボタンが押された時の処理
	/// </summary>
	UFUNCTION()
	void OnClickedQuit();

	/// <summary>
	/// 選択中UIの移動処理
	/// </summary>
	/// <param name="value">入力値</param>
	UFUNCTION()
	void SelectMove(const FInputActionValue& value);

	/// <summary>
	/// UIの選択処理
	/// </summary>
	/// <param name="value">入力値</param>
	UFUNCTION()
	void Select(const FInputActionValue& value);

	/// <summary>
	/// UI状態の更新
	/// </summary>
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
