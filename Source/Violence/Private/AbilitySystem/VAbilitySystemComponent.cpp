// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/VAbilitySystemComponent.h"

void UVAbilitySystemComponent::ApplyInitialEffects(const TArray<TSubclassOf<UGameplayEffect>>& GameplayEffects)
{
    if (!GetOwner() || !GetOwner()->HasAuthority()) return;
    
    if (GameplayEffects.IsEmpty()) return;
    
    for (const TSubclassOf<UGameplayEffect>& Effect : GameplayEffects)
    {
        if (!IsValid(Effect)) continue;

        ApplyGameplayEffectToSelf(Effect.GetDefaultObject(), 1, MakeEffectContext());
    }
}