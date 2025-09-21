// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/VAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/VGameplayAbility.h"
#include "VCoreTypes.h"

void UVAbilitySystemComponent::GiveInitialAbilities(const TArray<FVAbilitySet>& Abilities)
{
    if (!GetOwner() || !GetOwner()->HasAuthority()) return;

    if (Abilities.IsEmpty()) return;

    for (const FVAbilitySet& Ability : Abilities)
    {
        if (!Ability.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(Ability.Ability);
        AbilitySpec.SourceObject = GetAvatarActor();
        AbilitySpec.GetDynamicSpecSourceTags().AddTag(Ability.InputTag);

        GiveAbility(AbilitySpec);
    }
}

void UVAbilitySystemComponent::GiveInitialAbilities(const TArray<TSubclassOf<UVGameplayAbility>>& Abilities)
{
    if (!GetOwner() || !GetOwner()->HasAuthority()) return;

    if (Abilities.IsEmpty()) return;

    for (const TSubclassOf<UVGameplayAbility>& Ability : Abilities)
    {
        if (!IsValid(Ability)) continue;

        FGameplayAbilitySpec AbilitySpec(Ability);
        AbilitySpec.SourceObject = GetAvatarActor();

        GiveAbility(AbilitySpec);
    }
}

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

void UVAbilitySystemComponent::HandleAbilityInputPressed(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid()) return;

    for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
    {
        if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag)) continue;

        TryActivateAbility(AbilitySpec.Handle);
    }
}

void UVAbilitySystemComponent::HandleAbilityInputReleased(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid()) return;
}