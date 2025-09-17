// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "UI/VPlayerHUDWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/VAttributeSet.h"
#include "VValueGaugeWidget.h"

void UVPlayerHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    APawn* Pawn = GetOwningPlayerPawn();
    if (!Pawn) return;

    UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pawn);
    if (!AbilitySystemComponent) return;

    HealthGaugeWidget->InitializeWithAttribute(AbilitySystemComponent, UVAttributeSet::GetHealthAttribute(), UVAttributeSet::GetMaxHealthAttribute());
    ResourceGaugeWidget->InitializeWithAttribute(AbilitySystemComponent, UVAttributeSet::GetResourceAttribute(), UVAttributeSet::GetMaxResourceAttribute());
}