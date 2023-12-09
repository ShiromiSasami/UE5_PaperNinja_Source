// Fill out your copyright notice in the Description page of Project Settings.


#include "Others/C_UW_Title.h"

#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <InputMappingContext.h>

bool UC_UW_Title::Initialize()
{
	if(!Super::Initialize()) return false;


	_inputMove = LoadObject<UInputAction>(NULL, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Move.IA_Move'"));
	_inputSelect = LoadObject<UInputAction>(NULL, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Jump.IA_Jump'"));

	return true;
}

void UC_UW_Title::NativeConstruct()
{
	Super::NativeConstruct();

	if (Start_Button)
	{
		Start_Button->OnClicked.AddDynamic(this, &UC_UW_Title::OnClickedStart);
		_buttonID.Add(EButtonID::Start);
	}

	if (Quit_Button)
	{
		Quit_Button->OnClicked.AddDynamic(this, &UC_UW_Title::OnClickedQuit);
		_buttonID.Add(EButtonID::Quit);
	}

	auto eic = Cast<UEnhancedInputComponent>(GetOwningPlayer()->InputComponent);
	eic->BindAction(_inputMove, ETriggerEvent::Triggered, this, &UC_UW_Title::SelectMove);
	eic->BindAction(_inputSelect, ETriggerEvent::Triggered, this, &UC_UW_Title::Select);
	auto imc = LoadObject<UInputMappingContext>(NULL, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Default.IMC_Default'"), NULL, LOAD_None, NULL);

	if (auto controller = CastChecked<APlayerController>(GetOwningPlayer()))
	{
		if (auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(imc, 0);
		}
	}

	_currentIndex = 0;

	UpdateUI();
}

void UC_UW_Title::OnClickedStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Stage01_Top");
}

void UC_UW_Title::OnClickedQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}

void UC_UW_Title::SelectMove(const FInputActionValue& value)
{
	FVector2D vec = value.Get<FVector2D>();
	
	if(FMath::Abs(vec.Y) < 0.5) return;

	_currentIndex += vec.Y > 0 ? -1 : 1;
	_currentIndex = FMath::Clamp(_currentIndex, 0, _buttonID.Num() - 1);

	UpdateUI();
}

void UC_UW_Title::Select(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		switch (_buttonID[_currentIndex])
		{
		case EButtonID::Start:
			OnClickedStart();
			break;
		case EButtonID::Quit:
			OnClickedQuit();
			break;
		default:
			break;
		}
	}
}

void UC_UW_Title::UpdateUI()
{
	Start_Button->SetBackgroundColor(FColor::White);
	Quit_Button->SetBackgroundColor(FColor::White);
	switch (_buttonID[_currentIndex])
	{
	case EButtonID::Start:
		Start_Button->SetFocus();
		Start_Button->SetBackgroundColor(FColor::Blue);
		break;
	case EButtonID::Quit:	
		Quit_Button->SetFocus();
		Quit_Button->SetBackgroundColor(FColor::Blue);
		break;
	default:
		break;
	}
}
