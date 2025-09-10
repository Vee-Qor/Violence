// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "VAbilitySystemComponent.generated.h"

struct FVAbilitySet;

UCLASS()
class UVAbilitySystemComponent : public UAbilitySystemComponent
{
    GENERATED_BODY()

public:
    void GiveInitialAbilities(const TArray<FVAbilitySet>& Abilities);
    void ApplyInitialEffects(const TArray<TSubclassOf<UGameplayEffect>>& GameplayEffects);

    void HandleAbilityInputPressed(const FGameplayTag& InputTag);
    void HandleAbilityInputReleased(const FGameplayTag& InputTag);

};