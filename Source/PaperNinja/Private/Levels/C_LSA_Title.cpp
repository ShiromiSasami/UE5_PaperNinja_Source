// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/C_LSA_Title.h"

#include <Blueprint/UserWidget.h>

AC_LSA_Title::AC_LSA_Title()
{
}

void AC_LSA_Title::BeginPlay()
{
	Super::BeginPlay();

    const FString TitleWidgetPath = "/Game/Blueprints/TitleWidget.TitleWidget_c";
    if (const auto TitleWidgetClass = TSoftClassPtr<UUserWidget>(FSoftClassPath(*TitleWidgetPath)).LoadSynchronous())
    {
        CreateWidget<UUserWidget>(GetWorld(), TitleWidgetClass)->AddToViewport();
    }
}
