// Copyright 2025 Vee.Qor. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VCoreTypes.h"
#include "DataAssets/AbilitySets/VDefaultAbilitySet.h"
#include "VPlayerAbilitySet.generated.h"

UCLASS()
class UVPlayerAbilitySet : public UVDefaultAbilitySet
{
    GENERATED_BODY()

public:
    virtual void ApplyToASC(UVAbilitySystemComponent* ASC) const override;
    FORCEINLINE TArray<FVAbilitySet> GetInitialAbilities() const { return InitialAbilities; }

private:
    UPROPERTY(EditDefaultsOnly, Category = "Abilities")
    TArray<FVAbilitySet> InitialAbilities;
};