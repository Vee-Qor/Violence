// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "UI/VDeathWidget.h"

#include "Components/Button.h"
#include "Characters/VCharacter.h"

void UVDeathWidget::NativeConstruct()
{
    Super::NativeConstruct();

    RespawnBtn->OnClicked.AddDynamic(this, &UVDeathWidget::RespawnBtnClicked);
}

void UVDeathWidget::RespawnBtnClicked()
{
    APawn* Pawn = GetOwningPlayerPawn();
    if (!Pawn) return;

    AVCharacter* VCharacter = Cast<AVCharacter>(Pawn);
    if (!VCharacter) return;

    VCharacter->Server_RequestRespawn();
}