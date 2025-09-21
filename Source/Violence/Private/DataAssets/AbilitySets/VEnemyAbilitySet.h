// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/AbilitySets/VDefaultAbilitySet.h"
#include "VEnemyAbilitySet.generated.h"

class UVGameplayAbility;

UCLASS()
class UVEnemyAbilitySet : public UVDefaultAbilitySet
{
    GENERATED_BODY()

public:
    virtual void ApplyToASC(UVAbilitySystemComponent* ASC) const override;
    FORCEINLINE TArray<TSubclassOf<UVGameplayAbility>> GetInitialAbilities() const { return InitialAbilities; }

private:
    UPROPERTY(EditDefaultsOnly, Category = "Abilities")
    TArray<TSubclassOf<UVGameplayAbility>> InitialAbilities;

};