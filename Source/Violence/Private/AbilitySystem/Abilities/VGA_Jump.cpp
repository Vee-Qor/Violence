// Copyright 2025 Vee.Qor. All Rights Reserved.


#include "AbilitySystem/Abilities/VGA_Jump.h"

#include "Characters/VCharacter.h"
#include "VGameplayTags.h"

UVGA_Jump::UVGA_Jump()
{
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    SetAssetTags(VGameplayTags::Player_Ability_Jump.GetTag().GetSingleTagContainer());
    ActivationOwnedTags.AddTag(VGameplayTags::Player_Status_InAir);
}

bool UVGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
    const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
    AVCharacter* VCharacter = GetVCharacterFromActorInfo();
    if (!VCharacter || !VCharacter->CanJump())
    {
        return false;
    }

    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UVGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
    const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (!K2_CommitAbility())
    {
        K2_EndAbility();
        return;
    }

    if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
    {
        AVCharacter* VCharacter = GetVCharacterFromActorInfo();
        if (VCharacter)
        {
            VCharacter->Jump();
            VCharacter->LandedDelegate.RemoveAll(this);
            VCharacter->LandedDelegate.AddDynamic(this, &UVGA_Jump::OnCharacterLanded);
        }
    }
}

void UVGA_Jump::OnCharacterLanded(const FHitResult& Hit)
{
    K2_EndAbility();
}