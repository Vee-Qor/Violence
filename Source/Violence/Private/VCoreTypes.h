// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "GameplayTagContainer.h"
#include "VCoreTypes.generated.h"

class UVGameplayAbility;

USTRUCT(BlueprintType)
struct FVAbilitySet
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, meta = (Categories = "InputTag"))
    FGameplayTag InputTag;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UVGameplayAbility> Ability;

    bool IsValid() const;
};