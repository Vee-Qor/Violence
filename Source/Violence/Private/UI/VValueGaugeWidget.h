// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VValueGaugeWidget.generated.h"

class UAbilitySystemComponent;
class UProgressBar;
class UTextBlock;
struct FGameplayAttribute;
struct FOnAttributeChangeData;

UCLASS()
class UVValueGaugeWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;
    void InitializeWithAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);

private:
    UPROPERTY(meta=(BindWidget))
    UProgressBar* ProgressBar;

    UPROPERTY(meta=(BindWidget))
    UTextBlock* ValueDisplayText;

    void OnValueChanged(const FOnAttributeChangeData& ChangeData);
    void OnMaxValueChanged(const FOnAttributeChangeData& ChangeData);

    void UpdateDisplay() const;

    float CachedValue = 1.0f;
    float CachedMaxValue = 1.0f;
};