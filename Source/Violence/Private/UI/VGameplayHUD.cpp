// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "UI/VGameplayHUD.h"

#include "UI/VPlayerHUDWidget.h"

void AVGameplayHUD::BeginPlay()
{
    Super::BeginPlay();

    if (UVPlayerHUDWidget* PlayerHUDWidget = CreateWidget<UVPlayerHUDWidget>(GetWorld(), PlayerHUDWidgetClass))
    {
        PlayerHUDWidget->AddToViewport();
    }
}