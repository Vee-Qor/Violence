// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VPlayerHUDWidget.generated.h"

class UVResourceBarWidget;

UCLASS()
class UVPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta=(BindWidget))
    UVResourceBarWidget* HealthBarWidget;
};