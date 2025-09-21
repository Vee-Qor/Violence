// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "DataAssets/AbilitySets/VPlayerAbilitySet.h"

#include "AbilitySystem/VAbilitySystemComponent.h"

void UVPlayerAbilitySet::ApplyToASC(UVAbilitySystemComponent* ASC) const
{
    Super::ApplyToASC(ASC);

    if (ASC)
    {
        ASC->GiveInitialAbilities(GetInitialAbilities());
    }
}