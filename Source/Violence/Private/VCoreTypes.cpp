// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "VCoreTypes.h"

#include "AbilitySystem/Abilities/VGameplayAbility.h"

bool FVAbilitySet::IsValid() const
{
    return InputTag.IsValid() && Ability;
}