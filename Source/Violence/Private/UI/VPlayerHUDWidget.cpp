// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "UI/VPlayerHUDWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/VAttributeSet.h"
#include "VValueGaugeWidget.h"
#include "VGameplayTags.h"
#include "UI/VDeathWidget.h"

void UVPlayerHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    APawn* Pawn = GetOwningPlayerPawn();
    if (!Pawn) return;

    UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Pawn);
    if (!AbilitySystemComponent) return;

    HealthGaugeWidget->InitializeWithAttribute(AbilitySystemComponent, UVAttributeSet::GetHealthAttribute(), UVAttributeSet::GetMaxHealthAttribute());
    ResourceGaugeWidget->InitializeWithAttribute(AbilitySystemComponent, UVAttributeSet::GetResourceAttribute(), UVAttributeSet::GetMaxResourceAttribute());

    AbilitySystemComponent->RegisterGameplayTagEvent(VGameplayTags::Common_Status_Dead).AddUObject(this, &UVPlayerHUDWidget::StatusDeadTagUpdated);
}

void UVPlayerHUDWidget::StatusDeadTagUpdated(const FGameplayTag, int32 NewCount)
{
    const bool bIsDead = NewCount != 0;

    if (!DeathWidget && DeathWidgetClass)
    {
        DeathWidget = CreateWidget<UVDeathWidget>(this, DeathWidgetClass);
        if (DeathWidget) DeathWidget->AddToViewport();
    }

    if (DeathWidget)
    {
        DeathWidget->SetVisibility(bIsDead ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }

    if (APlayerController* PlayerController = GetOwningPlayer())
    {
        PlayerController->bShowMouseCursor = bIsDead;
        if (bIsDead)
        {
            PlayerController->SetInputMode(FInputModeGameAndUI{});
        }
        else
        {
            PlayerController->SetInputMode(FInputModeGameOnly{});
        }
    }
}