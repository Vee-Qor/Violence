// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGameplayAbility.h"

#include "Characters/VCharacter.h"

AVCharacter* UVGameplayAbility::GetVCharacterFromActorInfo() const
{
    if (CurrentActorInfo && CurrentActorInfo->AvatarActor.IsValid())
    {
        return Cast<AVCharacter>(CurrentActorInfo->AvatarActor.Get());
    }

    return nullptr;
}