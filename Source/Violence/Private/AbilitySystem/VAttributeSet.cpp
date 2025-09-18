// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/VAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UVAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
    Super::PreAttributeChange(Attribute, NewValue);

    if (Attribute == GetHealthAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
    }

    if (Attribute == GetResourceAttribute())
    {
        NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxResource());
    }
}

void UVAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
    }

    if (Data.EvaluatedData.Attribute == GetResourceAttribute())
    {
        SetResource(FMath::Clamp(GetResource(), 0.0f, GetMaxResource()));
    }
}

void UVAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UVAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UVAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UVAttributeSet, Resource, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UVAttributeSet, MaxResource, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UVAttributeSet, AttackSpeed, COND_None, REPNOTIFY_Always);
}

void UVAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UVAttributeSet, Health, OldHealth);
}

void UVAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UVAttributeSet, Health, OldMaxHealth);
}

void UVAttributeSet::OnRep_Resource(const FGameplayAttributeData& OldResource) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UVAttributeSet, Resource, OldResource);
}

void UVAttributeSet::OnRep_MaxResource(const FGameplayAttributeData& OldMaxResource) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UVAttributeSet, MaxResource, OldMaxResource);
}

void UVAttributeSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UVAttributeSet, AttackSpeed, OldAttackSpeed);
}