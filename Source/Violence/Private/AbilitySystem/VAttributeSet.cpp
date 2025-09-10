// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/VAttributeSet.h"

#include "Net/UnrealNetwork.h"

void UVAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UVAttributeSet, Health, COND_None, REPNOTIFY_Always);
    DOREPLIFETIME_CONDITION_NOTIFY(UVAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UVAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UVAttributeSet, Health, OldHealth);
}

void UVAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
    GAMEPLAYATTRIBUTE_REPNOTIFY(UVAttributeSet, Health, OldMaxHealth);
}