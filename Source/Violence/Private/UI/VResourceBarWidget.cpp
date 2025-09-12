// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "UI/VResourceBarWidget.h"

#include "AbilitySystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UVResourceBarWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UVResourceBarWidget::InitializeWithAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute,
    const FGameplayAttribute& MaxAttribute)
{
    if (!AbilitySystemComponent || !Attribute.IsValid() || !MaxAttribute.IsValid()) return;

    bool bFound = false;
    CachedValue = AbilitySystemComponent->GetGameplayAttributeValue(Attribute, bFound);
    CachedMaxValue = AbilitySystemComponent->GetGameplayAttributeValue(MaxAttribute, bFound);
    
    UpdateDisplay();

    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(this, &UVResourceBarWidget::OnValueChanged);
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MaxAttribute).AddUObject(this, &UVResourceBarWidget::OnMaxValueChanged);
}

void UVResourceBarWidget::OnValueChanged(const FOnAttributeChangeData& ChangeData)
{
    CachedValue = ChangeData.NewValue;
    UpdateDisplay();
}

void UVResourceBarWidget::OnMaxValueChanged(const FOnAttributeChangeData& ChangeData)
{
    CachedMaxValue = ChangeData.NewValue;
    UpdateDisplay();
}

void UVResourceBarWidget::UpdateDisplay() const
{
    if (!ValueDisplayText || !ProgressBar) return;

    ValueDisplayText->SetText(FText::AsNumber(CachedValue));

    const float SafeMaxValue = FMath::Max(1.0f, CachedMaxValue);
    ProgressBar->SetPercent(CachedValue / SafeMaxValue);
}