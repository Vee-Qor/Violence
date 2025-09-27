// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VDeathWidget.generated.h"

class UButton;

UCLASS()
class UVDeathWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta = (BindWidget))
    UButton* ContinueBtn;

    UPROPERTY(meta = (BindWidget))
    UButton* RespawnBtn;

    UPROPERTY(meta = (BindWidget))
    UButton* MainMenuBtn;

    UFUNCTION()
    void RespawnBtnClicked();
};