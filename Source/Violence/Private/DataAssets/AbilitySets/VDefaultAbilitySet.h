// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VDefaultAbilitySet.generated.h"

class UVAbilitySystemComponent;
class UVGameplayAbility;
class UGameplayEffect;

UCLASS()
class UVDefaultAbilitySet : public UDataAsset
{
    GENERATED_BODY()

public:
    virtual void ApplyToASC(UVAbilitySystemComponent* ASC) const;
    FORCEINLINE TArray<TSubclassOf<UGameplayEffect>> GetInitialEffects() const { return InitialEffects; }
    FORCEINLINE TArray<TSubclassOf<UVGameplayAbility>> GetPassiveReactionAbilities() const { return PassiveReactionAbilities; }

private:
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    TArray<TSubclassOf<UGameplayEffect>> InitialEffects;

    UPROPERTY(EditDefaultsOnly, Category = "Abilities")
    TArray<TSubclassOf<UVGameplayAbility>> PassiveReactionAbilities;
};