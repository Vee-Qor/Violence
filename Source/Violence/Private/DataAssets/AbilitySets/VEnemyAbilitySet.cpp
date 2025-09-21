// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "DataAssets/AbilitySets/VEnemyAbilitySet.h"

#include "AbilitySystem/VAbilitySystemComponent.h"

void UVEnemyAbilitySet::ApplyToASC(UVAbilitySystemComponent* ASC) const
{
    Super::ApplyToASC(ASC);

    if (ASC)
    {
        ASC->GiveInitialAbilities(GetInitialAbilities());
    }
}