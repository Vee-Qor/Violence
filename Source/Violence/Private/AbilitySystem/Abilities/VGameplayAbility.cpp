// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGameplayAbility.h"

#include "Characters/VCharacter.h"

AVCharacter* UVGameplayAbility::GetVCharacterFromActorInfo() const
{
    if (CurrentActorInfo)
    {

        return Cast<AVCharacter>(CurrentActorInfo->AvatarActor);
    }
    return nullptr;
}