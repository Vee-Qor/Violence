// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "UI/VValueGaugeWidget.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UVValueGaugeWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UVValueGaugeWidget::InitializeWithAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute,
    const FGameplayAttribute& MaxAttribute)
{
    if (!AbilitySystemComponent || !Attribute.IsValid() || !MaxAttribute.IsValid()) return;

    bool bFound = false;
    CachedValue = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);
    CachedMaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bFound);
    
    UpdateDisplay();

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UVValueGaugeWidget::OnValueChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UVValueGaugeWidget::OnMaxValueChanged);
}

void UVValueGaugeWidget::OnValueChanged(const FOnAttributeChangeData& ChangeData)
{
    CachedValue = ChangeData.NewValue;
    UpdateDisplay();
}

void UVValueGaugeWidget::OnMaxValueChanged(const FOnAttributeChangeData& ChangeData)
{
    CachedMaxValue = ChangeData.NewValue;
    UpdateDisplay();
}

void UVValueGaugeWidget::UpdateDisplay() const
{
    if (!ValueDisplayText || !ProgressBar) return;

    ValueDisplayText->SetText(FText::AsNumber(CachedValue));

    const float SafeMaxValue = FMath::Max(1.0f, CachedMaxValue);
    ProgressBar->SetPercent(CachedValue / SafeMaxValue);
}