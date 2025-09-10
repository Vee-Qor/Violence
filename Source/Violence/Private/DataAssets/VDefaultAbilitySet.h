// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VCoreTypes.h"
#include "Engine/DataAsset.h"
#include "VDefaultAbilitySet.generated.h"

class UVAbilitySystemComponent;
class UGameplayEffect;

UCLASS()
class UVDefaultAbilitySet : public UDataAsset
{
    GENERATED_BODY()

public:
    FORCEINLINE TArray<FVAbilitySet> GetInitialAbilities() const { return InitialAbilities; }
    FORCEINLINE TArray<TSubclassOf<UGameplayEffect>> GetInitialEffects() const { return InitialEffects; }

private:
    UPROPERTY(EditDefaultsOnly, Category = "Abilities")
    TArray<FVAbilitySet> InitialAbilities;

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
};