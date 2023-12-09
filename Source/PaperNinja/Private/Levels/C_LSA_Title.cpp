// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/C_LSA_Title.h"

#include <Blueprint/UserWidget.h>

AC_LSA_Title::AC_LSA_Title()
{
}

void AC_LSA_Title::BeginPlay()
{
	Super::BeginPlay();

    const FString TitleWidgetPath = "/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/TitleWidget.TitleWidget_c'";
    const auto TitleWidgetClass = LoadClass<UUserWidget>(NULL, *TitleWidgetPath);
    UUserWidget* titleWidget = CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass);
    titleWidget->AddToViewport();
}
