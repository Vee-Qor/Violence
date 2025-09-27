// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VPlayerHUDWidget.generated.h"

class UVDeathWidget;
class UVValueGaugeWidget;
struct FGameplayTag;

UCLASS()
class UVPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

private:
    UPROPERTY(meta=(BindWidget))
    UVValueGaugeWidget* HealthGaugeWidget;

    UPROPERTY(meta=(BindWidget))
    UVValueGaugeWidget* ResourceGaugeWidget;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UVDeathWidget> DeathWidgetClass;

    UPROPERTY()
    UVDeathWidget* DeathWidget;

    void StatusDeadTagUpdated(const FGameplayTag, int32 NewCount);
};