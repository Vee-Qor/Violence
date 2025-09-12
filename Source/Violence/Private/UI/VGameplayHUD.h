// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VGameplayHUD.generated.h"

class UVPlayerHUDWidget;

UCLASS()
class AVGameplayHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UVPlayerHUDWidget> PlayerHUDWidgetClass;
};