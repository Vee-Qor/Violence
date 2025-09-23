// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "DataAssets/AbilitySets//VDefaultAbilitySet.h"

#include "AbilitySystem/VAbilitySystemComponent.h"

void UVDefaultAbilitySet::ApplyToASC(UVAbilitySystemComponent* ASC) const
{
    if (ASC)
    {
        ASC->ApplyInitialEffects(GetInitialEffects());
        ASC->GiveInitialAbilities(GetPassiveReactionAbilities());
    }
}